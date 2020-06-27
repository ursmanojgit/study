import tkinter as tk
from tkinter import *
from easysettings import EasySettings
import threading
import time

sem = threading.Semaphore()
settings = EasySettings("myconfigfile.conf")

####### GUI ##############
master = tk.Tk()
master.geometry("1200x400");
master.title("Tizen Network Image Updater")
tk.Label(master, 
        text="Target IP Address", anchor="e", justify=tk.LEFT).grid(row=0)
tk.Label(master, 
        text="Serial Port", anchor="e", justify=tk.LEFT).grid(row=1)
tk.Label(master, 
        text="Image Url", anchor="e", justify=tk.LEFT).grid(row=2)

e1 = tk.Entry(master, width=20, justify=tk.LEFT)
e2 = tk.Entry(master, width=20, justify=tk.LEFT)
e3 = tk.Entry(master, width=100, justify=tk.LEFT)
progressText = tk.StringVar()
#####################################


def show_entry_fields():
    global sem
    print("First Name: %s\nLast Name: %s" % (e1.get(), e2.get()))
    settings.set('TARGET_IP', e1.get())
    settings.set('PORT', e2.get())
    settings.set('URL', e3.get())
    settings.save()
    #update URL and PORT variables, and break while loop in seret
    sem.release() #another thred will wakeup

def show_gui():


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

    e1.grid(row=0, column=1, sticky=tk.W)
    e2.grid(row=1, column=1, sticky=tk.W)
    e3.grid(row=2, column=1, sticky=tk.W)

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

## progress message ###
    
    tk.Message( master, textvariable=progressText, relief=tk.FLAT, width=1000).grid(row=6, 
                                                        column=1, 
                                                        sticky=tk.W)
    progressText.set("Hey!? How are you doing?Hey!? How are you doing?Hey!? How are you doing?Hey!? How are you doing?Hey!? How are you doing?Hey!? How are you doing?")
#################
    tk.mainloop()



def seret_thread(num): 
    """ 
    function to print cube of given num 
    """
    global sem
    print("Waiting....") 
    sem.acquire()
    print("wait done!, will change progress to 100%") 
    time.sleep(5)
    progressText.set("Image flashed: 100%")
    
  

  
if __name__ == "__main__": 
    #sem.acquire()#acquire so that worker thread can wait, and flashimage wil release it
    # creating thread 
    t1 = threading.Thread(target=seret_thread, args=(10,)) 
  
    # starting thread 1 
    t1.start() 

    show_gui()
  
    # wait until thread 1 is completely executed 
    t1.join() 
  
    # both threads completely executed 
    print("Done!") 
    

    