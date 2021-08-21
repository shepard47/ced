BEGIN{system("rm -f gl.h gl.c")
	print "void\nloadgl(void){\n" >> gl.c }
{gsub(/GLuint/,"uint")}
/^#define/{print $0 >> "gl.h"}
/^GLAPI/{print "extern " $2 " " "(*" $4 ")" >> "gl.h"
	print $2 " " "(*" $4 ")" >> "gl.c"
	$1=$2=$3=$4=""; print $0 >> "gl.h"
	$1=$2=$3=$4=""; print $0 >> "gl.c"}

