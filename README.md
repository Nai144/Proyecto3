# Proyecto3
# link al video
#https://drive.google.com/file/d/1E6wvXWy4b3oB_ve55hvgVW0Xd6ACDORN/view?usp=sharing
El programa nesesita para funcionar un config el cual fue subido en forma de txt. 
El programa ocupa un mapa para asociar el nombre de los algoritmos con sus resultados, al inicio del main
se lee el archivo config para saber en que rango de valores se trabajara en cada modo, se creara un valor 
aleatorio en esos rangos. Se generan 2 arreglos el arreglo original y el arreglo duplicado, el arreglo
original tendra los datos a trabajar, mientras que el duplicado sera con el cual se trabajara.
por cada modo se llamara a la funcion ejecutarcarrera la cual creara 7 arreglos, uno para cada algoritmo
y se los entrara a una funcion Time + nombre del algoritmo. El resultado se almacera en un vector de 
resultados. Las funciones time estan encargadas de determinar en que modo estamos y que algoritmo debe ser 
usado, el ascendente o descendente. Esto se realizo de esta manera para no agregar condiciones a los algoritmos
de ordenamiento y que no tomen tiempo extra en esto, finalmente al tener los resultados llamamos a la funcion, 
mostrar resultados a la cual le entregamos el vector resultados y el mapa de los algoritmos y sus tiempos, 
estafuncion ordenado los tiempos para luego comparar el timepo de la posicion 0 con el mapa, de esta manera 
se encuentra el nombre del algoritmo con el mejor tiempo, este metedo es util, ya que, si el cambiamos el valor
del for nos mostrara todas los resultados ordenados siendo mas faciles de analizar.
