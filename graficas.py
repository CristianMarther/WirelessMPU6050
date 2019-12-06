import matplotlib.pyplot as plt
import sqlite3

ruta = input("Ingresa nombre de archivo: *por defecto IMU6050*\n ")

connect = sqlite3.connect("C:/Users/Guadalupe/AppData/LocalLow/DefaultCompany/MoviendoCuerpo/" + ruta)



cursor = connect.cursor()

cursor.execute('select * from sensores')

rows = cursor.fetchall()

x =[]

x1 =[]
y1 =[]

x2 = []
y2 = []

x3 =[]
y3 =[]

x4 = []
y4 = []

acc = []

for row in rows:
	x.append(row[0])
	x1.append(row[1])
	y1.append(row[2])
	x2.append(row[3])
	y2.append(row[4])
	x3.append(row[5])
	y3.append(row[6])
	x4.append(row[7])
	y4.append(row[8])
	acc.append(row[9])

#x = [1,2,3,4,5,6,7,8,9]
#y = [1,2,3,4,5,6,7,8,9]

connect.close()

longi = len(x)

fig = plt.figure()

fig.suptitle('Angulos', fontsize = 16 )

ax1 = fig.add_subplot(321)

ax2 = fig.add_subplot(323)

ax3 = fig.add_subplot(322)

ax4 = fig.add_subplot(324)

ax5 = fig.add_subplot(325)

for indice in range(longi):
	ax1.plot(x[indice], x1[indice], marker='.', color = 'b')
	ax1.plot(x[indice], y1[indice], marker='.', color = 'r')

ax1.set_title('Tibia izquierda')
ax1.set_xlabel('Muestras')
ax1.set_ylabel('Angulo')

for indice in range(longi):
	ax2.plot(x[indice], x2[indice], marker='.', color = 'b')
	ax2.plot(x[indice], y2[indice], marker='.', color = 'r')

ax2.set_title('Femur izquierdo')
ax2.set_xlabel('Muestras')
ax2.set_ylabel('Angulo')

for indice in range(longi):
	ax3.plot(x[indice], x3[indice], marker='.', color = 'b')
	ax3.plot(x[indice], y3[indice], marker='.', color = 'r')

ax3.set_title('Tibia derecha')
ax3.set_xlabel('Muestras')
ax3.set_ylabel('Angulo')

for indice in range(longi):
	ax4.plot(x[indice], x4[indice], marker='.', color = 'b')
	ax4.plot(x[indice], y4[indice], marker='.', color = 'r')

ax4.set_title('Femur derecho')
ax4.set_xlabel('Muestras')
ax4.set_ylabel('Angulo')


for indice in range(longi):
	ax5.plot(x[indice], acc[indice], marker='.', color = 'g')

ax5.set_title('Aceleracion Cadera')
ax5.set_xlabel('Muestras')
ax5.set_ylabel('m/s^2')


plt.ion()

plt.show()


entrada = input('presiona enter para cerrar')