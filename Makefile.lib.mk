LIB_IO= can_readf.c\
		get_next_line.c\
		get_next_line_utils.c
LIB_IO:= $(addprefix io/, ${LIB_IO})

LIB_STR=ft_strchr.c\
		ft_strstr.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_strlen.c\
		ft_strnew.c\
		ft_strdup.c\
		ft_strndup.c\
		ft_strdel.c\
		ft_strclr.c\
		ft_strcpy.c\
		ft_strncpy.c\
		ft_strjoin.c\
		ft_strspn.c
LIB_STR:= $(addprefix str/, ${LIB_STR})

LIB_MEM=ft_memcpy.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memsize.c\
		ft_memdel.c\
		ft_realloc.c
LIB_MEM:= $(addprefix mem/, ${LIB_MEM})

LIB_CHAR=	ft_isspace.c\
			ft_isgraph.c\
			ft_isalnum.c
LIB_CHAR:= $(addprefix char/, ${LIB_CHAR})

LIB_SOURCES= $(addprefix lib/, ${LIB_IO} ${LIB_STR} ${LIB_MEM} ${LIB_CHAR})
LIB_OBJS= $(subst .c,.o,$(LIB_SOURCES))
