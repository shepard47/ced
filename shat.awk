BEGIN{printf "char *%s = {\n", ARGV[1]}
{printf "\t\"%s\\n\"\n", $0}
END{printf "};\n"}


