#ifndef _ADAPTOR_UTILS_H
#define _ADAPTOR_UTILS_H

extern int adaptor_family;
extern unsigned int number_of_fields;

char *get_struct_adaptor_string(char *str, fieldsub *m) {
	assert(adaptor_family==4 || adaptor_family == 14);
	int len=0;
	int i;
	char type_varname[10];
	char my_str[ADAPTOR_STR_LEN] = {'\0'};
	str[0]='\0';
	for(i=0; i<number_of_fields; i++) {
		sprintf(my_str, "f%c_type=0x%lx f%c_size=0x%x f%c_n=0x%x ", '1'+i,
				m[i].type, '1'+i, m[i].size, '1'+i, m[i].n);
		len = sprintf(str, "%s%s", str, my_str);
		str[len]='\0';
	}
	assert(len<= ADAPTOR_STR_LEN);
	return str;
}
#endif