
$(NAME)

all:

clean:

fclean:

re:

bonus:

gcc parser.c libft/libft.a -o printmap.out
gcc main.c libmlx.dylib -framework OpenGL -framework AppKit -o window.out

gcc main.c parser.c errors.c libft/libft.a -g libmlx.dylib -framework OpenGL -framework AppKit -o window.out -Wall -Werror -Wextra

gcc main.c parser.c errors.c screenshot.c sprite.c move.c inits.c parser_map.c -g libft/libft.a libmlx.dylib -framework OpenGL -framework AppKit -o cub3D -Wall -Werror -Wextra


// построение стен
PLR - игрок
    - X, Y, dir - координаты и направление взгляда

PoV - player.dir
FoV - (M_PI / 3) - 60 градусов
    - player.start - PoV-(FoV/2) - начало угла обзора
    - player.end   - PoV+(FoV/2) - конец угла обзора
    - step - FoV/800		 - шаг
PP  - План Проекции
800х640 - map.max_y, map.max_x
400х320 - центр PP
692 - Расстояние до PP - (PP.x/2) / tan(FoV/2) = (800/2)/tan(M_PI/3 * 1/2) = 692.820323
0.075 - Угл между соседними лучами - 60/800 = 0.075

Зависимость между PLR и PP - 

Высота столбца - t = Высота текстуры / на до столбца * расстояние до PP
t = 1/len*692
Точка отрисовки столбца = высота PP / 2 - высота столбца / 2
ty = 640/2-t/2

// пробрасываете лучей
P (Px 0.5, Py 2.5) - расположение игрока
A (Ax 1.8, Ay 2.0) 
B (Bx 1.0, By 2.6)
C (Cx 2.3, Cy 1.0)
D (Dx 2.9, Dy 0.0)
E (Ex 3.0, Ey 0.8) (Ex 0.0, Ey 0.5)

Ya = 64	 высота куба
Xa = Cx(2.3) - Ax(1.8) = 0.5

1.
Нахождение первой точки горизонтального пересечения  
  Если луч смотрит вверх 
    Ay = Round_Down(py / Ya) * Ya - 1 
  Если смотрит вниз
    Ay = Округление_вниз(py / Ya) * Ya + Ya
py = Ya * Py = 64 * 2.5 + 64(так как 0 тоже куб) = 224
Ay = 224/64 * 64 - 1 = 191

Ax = Px + (Py - Ay) / tan(какой-то угл) = 96 + (224 - 191) / tan(60) = около 115
Координата сетки Ax составляет 115/64 = 1

2.
Поиск Ya
Если луч смотрит вверх
Ya = -64
Если вниз
Ya = 64

3.
Поиск Xa
Xa = 64 / tan (угла)60 = 36

4.
Следующая координата
Cx = Ax + Xa = 115 + 36 = 151
Cy = Ay + Ya = 191 - 64 = 127
Преобразование в сетку
Cx = 151/64 = 2
Cy = 127/64 = 1

5.
Повтор 4. Пока не будет стена


1.
Поиск первого вертикального пересечения
  Если луч вправо
    Bx = Round_Down(Px/64) * 64 + 64
  Если влево
    Bx = Округлить_вниз(Px/64) * 64 - 1
Ay = Py + (Px - Ax) * tan(угл)

2.
Найти Xa
  Если луч вправо
    Xa = +64
  Если влево
    Xa = -64

3.
Найти Ya
  Ay = Py + (Px - Ax) * tan(угл)

4.
Если есть стена, то рассчитать расстояние, если нет то 5.

5.
Повторять пока не будет найдена стена
Xnew = Xold + Xa
Ynew = Yold + Ya





