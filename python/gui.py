import tkinter as tk
from easysettings import EasySettings

settings = EasySettings("myconfigfile.conf")

def show_entry_fields():
    print("First Name: %s\nLast Name: %s" % (e1.get(), e2.get()))
    settings.set('TARGET_IP', e1.get())
    settings.set('PORT', e2.get())
    settings.set('URL', e3.get())
    settings.save()
    #update URL and PORT variables, and break while loop in seret

master = tk.Tk()
master.geometry("800x400");
master.title("Tizen Network Image Updater")
tk.Label(master, 
         text="Target IP Address").grid(row=0)
tk.Label(master, 
         text="Serial Port").grid(row=1)
tk.Label(master, 
         text="Image Url").grid(row=2)

e1 = tk.Entry(master, width=20)
e2 = tk.Entry(master, width=20)
e3 = tk.Entry(master, width=100)

if settings.has_option('TARGET_IP'):
    ip=settings.get('TARGET_IP')
    port=settings.get('PORT')
    url=settings.get('URL')
else:
    ip="10.88.98.101"
    port="COM1"
    url="http://samsung.casfs.com/sdfsadf/asfas/sadfas"


e1.insert(10, ip)
e2.insert(10, port)
e3.insert(10, url)

e1.grid(row=0, column=1)
e2.grid(row=1, column=1)
e3.grid(row=2, column=1)

tk.Button(master, 
          text='Quit', 
          command=master.quit).grid(row=3, 
                                    column=0, 
                                    sticky=tk.W, 
                                    pady=4)
tk.Button(master, 
          text='Flash Image', command=show_entry_fields).grid(row=3, 
                                                       column=1, 
                                                       sticky=tk.W, 
                                                       pady=4)

tk.mainloop()