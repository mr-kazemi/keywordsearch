from graphics import *
import math

list_of_colors=['AliceBlue','AntiqueWhite','Aqua','Aquamarine','Azure', 'Beige','Bisque','Black','BlanchedAlmond','Blue','BlueViolet','Brown','BurlyWood','CadetBlue','Chartreuse','Chocolate'
                ,'Coral','CornflowerBlue','Cornsilk','Crimson','Cyan','DarkBlue','DarkCyan','DarkGoldenRod','DarkGray','DarkGreen','DarkKhaki','DarkMagenta','DarkOliveGreen'
                ,'DarkOrange','DarkOrchid','DarkRed','DarkSalmon','DarkSeaGreen','DarkSlateBlue','DarkSlateGray','DarkTurquoise','DarkViolet','DeepPink','Gold','GoldenRod'
                ,'GreenYellow','IndianRed','Indigo','LightCoral','LightGray','LightGreen','Peru','Purple','Violet','Yellow','YellowGreenn']


#For opening a grafic window
win = GraphWin("graphic", 4000, 4000)
f=open("C:\\Users\\Fatemi\\Desktop\\PP.txt","r")#This file consists of datas
f1=f.readlines()
count = 0
grid_points_new=[]#This list saves gird points
list1=[]
diam_point1=[]#This list saves first point of diamater
diam_point2=[]#This list saves second point of diamater

#Reading that file and each data locates in the correct list separately
for x in f1:
    b = ""
    for i in x:
        if i.isdigit() == True or i == '.':
            b += i            
        else:                       
            count += 1
            if count == 2:
                a= float(b)           
            elif count == 3 or count ==4:
                diam_point1.append(float(b))
            elif count == 5 or count ==6:
                diam_point2.append(float(b))
            elif(count>=7 and count%3 == 1):  
                list1=[]
                list1.append(int(b))              
            elif(count>=7 and count%3 == 2): 
                list1.append(int(b))               
            elif(count>=7 and count%3 == 0): 
                list1.append(int(b))               
                grid_points_new.append(list1)            
                
            b = ""    
change = 20        
c_a= int(change*a)
      
#Drawing grid    
for i in range(0,4000,c_a):  
   li = Line(Point(0,i),Point(4000,i)) 
   li.setFill('LightGray')
   li.draw(win) 
   
for i in range(0,4000,c_a):
   li = Line(Point(i,0),Point(i,4000)) 
   li.setFill('LightGray')
   li.draw(win)

#Drawing points of the grid 
g = grid_points_new.__len__()
for i in range(0,g):   
    cr=Circle(Point((c_a*grid_points_new[i][0]),(c_a*grid_points_new[i][1])),8)    
    cr.setFill(list_of_colors[grid_points_new[i][2]-1])  
    cr.draw(win)
     
    t = Text(Point((c_a*grid_points_new[i][0]),(c_a*grid_points_new[i][1])),str(grid_points_new[i][2]))
    t.setSize(9)
    t.draw(win)   
    
pt_diam=[c_a*int((diam_point1[0]+diam_point2[0])/a)/2, c_a*int((diam_point1[1]+diam_point2[1])/a)/2]#Calcuting the center of the diamater
d= math.sqrt((diam_point1[0]-diam_point2[0])**2 + (diam_point1[1]-diam_point2[1])**2))#Calcuting the length of the diamater
diam= change/2*(d)

#Drawing the first point of the diamater
c1 =Circle(Point(c_a*int(diam_point1[0]/a),c_a*int(diam_point1[1]/a)),10)
for j in range(0,grid_points_new.__len__()):
    if(int(diam_point1[0]/a) == grid_points_new[j][0] and int(diam_point1[1]/a) == grid_points_new[j][1]):
        c1.setFill(list_of_colors[grid_points_new[j][2]-1])
        break
c1.draw(win)
t = Text(Point(c_a*int(diam_point1[0]/a),c_a*int(diam_point1[1]/a)), "c1")
t.setSize(9)
t.draw(win)

#Drawing the second point of the diamater
c2 =Circle(Point(c_a*int(diam_point2[0]/a),c_a*int(diam_point2[1]/a)),10)
for j in range(0,grid_points_new.__len__()):
    if(int(diam_point2[0]/a) == grid_points_new[j][0] and int(diam_point2[1]/a) == grid_points_new[j][1]):
        c2.setFill(list_of_colors[grid_points_new[j][2]-1])        
        break
c2.draw(win)
t = Text(Point(c_a*int(diam_point2[0]/a),c_a*int(diam_point2[1]/a)), "c2")
t.setSize(9)
t.draw(win)

#Drawing the circle mentioned
circle=Circle(Point(pt_diam[0],pt_diam[1]),diam)
circle.setOutline("MidnightBlue")
circle.draw(win)

win.getMouse() # Pause to view result
win.close()    # Close window when done
