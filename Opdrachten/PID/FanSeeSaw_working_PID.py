""" 
@author: Bart Bozon 
TkInter script to simulate a fan see saw
# time  prop_setpoint prop_speed distance  setpoint 

"""  

from tkinter import Tk,Canvas    
import math  
  
 
class SeeSaw():  
    def __init__(self, canvas):  
        self.canvas=canvas
        self.setpoint=0.3
        self.objects=[]
        self.x=[]
        self.y=[]
        self.length=200
        self.prop_speed=1
        self.prop_setpoint=100
        self.prop_force_coef=0.006
        self.prop_angle=0
        self.dt=0.003
        self.omega=0
        self.error=0
        self.error_prev=0
        self.error_sum=0
        self.air_resistance=0.0001
        self.inbalancemass=0.05      # kg
        self.g=9.81                 # ms-2
        self.inertia=0.1
        self.torque=0
        self.objects.append(canvas.create_oval(-5,-5,5,5,fill='black'))
        self.objects.append(canvas.create_oval(-5,-5,5,5,fill='black'))
        self.objects.append(canvas.create_oval(-3,-3,3,3,fill='red'))
        for i in range (20):
            self.objects.append(canvas.create_oval(-1,-1,1,1,fill='black'))
        self.objects.append(canvas.create_oval(296,196,304,204))
        for i in range (len (self.objects)):
            self.x.append(0)
            self.y.append(0)       
        self.alfa=0
        self.t=0
        
    def move_to_new_pos(self,item_num,x,y):  
        deltax=x-self.x[item_num]
        deltay=y-self.y[item_num]
        self.x[item_num]=x
        self.y[item_num]=y
        self.canvas.move(self.objects[item_num],deltax,deltay)  
    
    def move(self):
        self.t+=self.dt
        self.torque=-self.inbalancemass*self.g*math.cos(self.alfa)-self.omega*abs(self.omega)*self.air_resistance+self.prop_speed*self.prop_force_coef
        self.omega+=(self.torque/self.inertia)*self.dt
        self.alfa+=self.omega*self.dt
        if self.alfa>math.pi/3:
            self.alfa=math.pi/3
            if self.omega>0:
                self.omega=0
        if self.alfa<-math.pi/3:
            self.alfa=-math.pi/3
            if self.omega<0:
                self.omega=0
        distance =0.3*(1+math.sin(self.alfa))
        ###################################################################
        if (self.t%60)>30: self.setpoint=0.4
        self.error=self.setpoint-distance
        
        
        kp = 300
        ki = 300
        kd = 400
        
        self.error = self.setpoint - distance
        self.error_sum += self.error * self.dt
        self.error_div = (self.error - self.error_prev) / self.dt
        self.prop_setpoint = kp * self.error + ki * self.error_sum + kd * self.error_div
        self.error_prev = self.error        

        
        ###################################################################
        if self.prop_setpoint>100: self.prop_setpoint =100
        if self.prop_setpoint<0: self.prop_setpoint =0        
        self.prop_speed=0.95*self.prop_speed+0.05*self.prop_setpoint    
        print (int(self.t),int(self.prop_setpoint),int(self.prop_speed),int(distance*100)/100,int(self.setpoint*100)/100)
        self.prop_angle+=self.prop_speed*self.dt
        self.move_to_new_pos(0,300-self.length*1.2*math.cos(self.alfa+3.1415),200+self.length*1.2*math.sin(self.alfa+3.1415))
        self.move_to_new_pos(1,300-self.length*0.8*math.cos(self.alfa+3.1415),200+self.length*0.8*math.sin(self.alfa+3.1415))
        self.move_to_new_pos(2,300-self.length*(1+0.2*math.sin(self.prop_angle))*math.cos(self.alfa+3.1415),200+self.length*(1+0.2*math.sin(self.prop_angle))*math.sin(self.alfa+3.1415))
        for i in range (3,23):
            self.move_to_new_pos(i,300-self.length*((i-14)/11)*math.cos(self.alfa+3.1415),200+self.length*((i-14)/11)*math.sin(self.alfa+3.1415))
        self.canvas.after(1, self.move)  

    
               
  
# Initialize root Window and canvas.  
root = Tk()  
root.title("SeeSaw")  
root.resizable(False,False)  
canvas = Canvas(root, width = 600, height = 400)  
canvas.pack()  
  
# Creating 1 sun, 1 asteroid, 2 planets and 2 moons.   
seesaw = SeeSaw(canvas)  
  
seesaw.move()  
  
# Run simulation.  
root.mainloop()  

