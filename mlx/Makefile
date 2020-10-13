#
#

NOM=libmlx.a
#HEADER = mlx.h
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11 -Wno-deprecated-declarations

# -Wno-deprecated-declarations dont show warnings about OpenGl not working

all: $(NOM)

$(NOM):	$(OBJ)
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)

#%.o: %.c $(HEADER)
#	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app

re: clean all

#	*~ matches all files in the current directory that end with ~. 
#	Why would you have such a file? Because when you use emacs to edit a file foo, 
#	it will leave a backup copy under foo~ by default. 
#	So this is intended to remove emacs backup files.
