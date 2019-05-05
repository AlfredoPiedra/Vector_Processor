import Tkinter as tk
import tkFileDialog as filedialog
import tkMessageBox as messagebox
from VectorParser import *

#-----------------------------------------------------------------------------
#           GLOBAL VARIABLES
#-----------------------------------------------------------------------------
file_name = ""
has_save = False
#-----------------------------------------------------------------------------
#           EDITOR  
#-----------------------------------------------------------------------------
class TextLineNumbers(tk.Canvas):
    
    def __init__(self, *args, **kwargs):
        
        tk.Canvas.__init__(self, *args, **kwargs)
        self.config(bg = 'red4')
        self.textwidget = None
        
    def attach(self, text_widget):

        self.textwidget = text_widget

    def redraw(self, *args):
        
        self.delete("all")
        i = self.textwidget.index("@0,0")
        
        while True :

            dline= self.textwidget.dlineinfo(i)
            if dline is None: break

            y = dline[1]
            linenum = str(i).split(".")[0]
            
            self.create_text(2,y,anchor="nw", text=linenum, fill = 'snow',font = ("Courier","14","bold"))
            i = self.textwidget.index("%s+1line" % i)
            
class CustomText(tk.Text):
    
    def __init__(self, *args, **kwargs):

        tk.Text.__init__(self, *args, **kwargs)
        self.bind('<Control-c>', self.copy)
        self.bind('<Control-x>', self.cut)
        self.bind('<Control-v>', self.paste)

        self._orig = self._w + "_orig"
        self.tk.call("rename", self._w, self._orig)
        self.tk.createcommand(self._w, self._proxy)

    def copy(self, event=None):

        try:
            self.clipboard_clear()
            text = self.get("sel.first", "sel.last")
            self.clipboard_append(text)

        except:
            print("Error on Copy: First selected the text")
    
    def cut(self, event):

        try:
            self.copy()
            self.delete("sel.first", "sel.last")

        except:
            print("Error on Cut: First selected the text")

    def paste(self, event):

        try:
            text = self.selection_get(selection='CLIPBOARD')
            self.insert('insert', text)

        except:
            print("Error on Paste: First selected the text")
        
    def _proxy(self, *args):

        cmd = (self._orig,) + args
        result = self.tk.call(cmd)

        if (args[0] in ("insert", "replace", "delete") 
            or args[0:3] == ("mark", "set", "insert")
            or args[0:2] == ("xview", "moveto") 
            or args[0:2] == ("xview", "scroll") 
            or args[0:2] == ("yview", "moveto") 
            or args[0:2] == ("yview", "scroll")
        ):
            self.event_generate("<<Change>>", when="tail")

        return result

class Example(tk.Frame):
    
    def __init__(self, *args, **kwargs):
        
        tk.Frame.__init__(self, *args, **kwargs)

        self.text = CustomText(self)
        self.vsb = tk.Scrollbar(orient="vertical", command=self.text.yview)

        self.text.configure(yscrollcommand=self.vsb.set)
        self.text.tag_configure("bigfont", font=("Courier", "24", "bold"))

        self.linenumbers = TextLineNumbers(self, width=30)
        self.linenumbers.attach(self.text)

        self.vsb.pack(side="right", fill="y")
        self.linenumbers.pack(side="left", fill="y")
        self.text.pack(side="right", fill="both", expand=True)

        self.text.bind("<<Change>>", self._on_change)
        self.text.bind("<Configure>", self._on_change)

    def _on_change(self, event):
        
        self.linenumbers.redraw()
#-----------------------------------------------------------------------------
#           INTERFAZ
#-----------------------------------------------------------------------------
if __name__ == "__main__":
    
    root = tk.Tk(className = '_Vector ASIP_')
    root.minsize(800,300)

    root_title = tk.Label(text="Vector ASIP",
                          bg = 'black',
                          fg = 'dodger blue')
    root_title.config(font = ("Courier","30","bold"))
    root_title.pack()
    
    root_separator = tk.Frame(height=2,
                              bd=1,
                              relief=tk.SUNKEN)
    root_separator.grid_propagate(False)
    root_separator.grid_rowconfigure(0,weight = 1)
    root_separator.grid_columnconfigure(0,weight = 1)
    root_separator.pack(fill=tk.X,
                        padx=5,
                        pady=5)     

    root_text_area = Example(root)
    root_text_area.pack(side="top",
                        fill="both",
                        expand=True)
    root_text_area.text.config(bg = 'snow',
                               fg = 'black',
                               insertbackground = 'dodger blue',
                               undo = True,
                               exportselection = True,
                               font = ("Courier","14","bold"))
#-----------------------------------------------------------------------------
#           FUNCTIONS
#-----------------------------------------------------------------------------
    def new_file():
        
        if len(root_text_area.text.get('1.0',tk.END+'-1c')) > 0:

            if messagebox.askyesno('Save?','Want to save?'):

                save_as_file()

        root_text_area.text.delete('1.0',tk.END)
        file_name = ""

        global has_save
        has_save = True
    
    def open_file():
        
        File = filedialog.askopenfile(parent = root,
                                      mode = 'rb',
                                      title = 'Select a asm file',
                                      filetypes = (("Text File",".txt"),("All Files","*.*")))
        if File != None:

            global file_name
            global has_save
            contents = File.read()

            root_text_area.text.delete('1.0',tk.END)
            root_text_area.text.insert('1.0',contents)

            file_name = File.name
            File.close()

            has_save = True

    def save_as_file():

        File = filedialog.asksaveasfile(mode = 'w',
                                        defaultextension = ".txt",
                                        filetypes = (("Text File",".txt"),("All Files","*.*")))
        if File != None:
            global file_name
            global has_save

            data = root_text_area.text.get('1.0',tk.END+'-1c')

            File.write(data)
            file_name = File.name
            File.close()
            
            has_save = False

    def save_file():

        global file_name
        global has_save

        File = open(file_name,'w')
        data = root_text_area.text.get('1.0',tk.END+'-1c')

        File.write(data)
        has_save = False
        
        File.close()
        
    def on_exit():

        if messagebox.showinfo("Quit","You want to quit?"):

            if  len(root_text_area.text.get('1.0',tk.END+'-1c')) > 0 and has_save:

                if messagebox.askyesno("Save?","Want to save?"):

                    if messagebox.askyesno("Same file","Want to save on the current file?"):

                        save_file()

                    else:

                        save_as_file() 

            root.destroy()

    def re_do(self):
        
        try:   

            root_text_area.text.edit_redo()

        except:

            pass
    
    def do_parse():

        # Get the instructions from the text area
        lines = root_text_area.text.get("1.0", tk.END+'-1c').splitlines()

        # Get the codified instructions
        assembly = parse_program(lines)
    
        if assembly[0] == -1:

            messagebox.showinfo("Error","Syntax error on line "
                                + str(assembly[1])
                                + ": " +assembly[2])

        else:

            File = filedialog.asksaveasfile(mode = 'w',
                                            defaultextension = ".txt",
                                            filetypes = (("Text File",".txt"),("All Files","*.*")))
            if File != None:
                
                File.writelines(assembly[1])
                File.close()

            else:

                messagebox.showinfo("Error","Error opening the generate destiny file")
            
#-----------------------------------------------------------------------------
#           MENU
#-----------------------------------------------------------------------------
    menu = tk.Menu(root)
    
    root.config(menu = menu,
                bg = 'black')

    fileMenu = tk.Menu(menu)

    menu.add_cascade(label = "File",
                     menu = fileMenu)

    fileMenu.add_command(label = "New", command = new_file)
    fileMenu.add_command(label = "Open...", command = open_file)
    fileMenu.add_command(label = "Save", command = save_file)
    fileMenu.add_command(label = "Save as...", command = save_as_file)
    fileMenu.add_separator()
    fileMenu.add_command(label = "Exit", command = on_exit)

    parserMenu = tk.Menu(menu)

    menu.add_cascade(label = "Execute",menu = parserMenu)
    parserMenu.add_command(label = "Generate...", command = do_parse)

    helpMenu = tk.Menu(menu)
    menu.add_cascade(label = "Help", menu = helpMenu)

    helpMenu.add_command(label = "ISA")
    helpMenu.add_command(label = "Syntax")
    helpMenu.add_command(label = "Codification")

    root.protocol("WM_DELETE_WINDOW", on_exit)
    root.bind('<Control-y>',re_do)
    root.mainloop()

