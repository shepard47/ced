BEGIN{printf "reading from %s\n", ARGV[1]}
{gsub(/ comment="*"/,"")}

/<enum /{split($3,n,"=") split($2,v,"=")
print "#define " 
substr(n[2],2,length(n[2])-2) " "
substr(v[2],2,length(v[2])-2)} 1
  
