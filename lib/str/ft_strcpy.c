char *ft_strcpy(char *const dst, const char *src)
{
	char *dst_ptr;

	dst_ptr = dst;
	while (*src)
	{
		*dst_ptr = *src;
		src++;
		dst_ptr++;
	}
	*dst_ptr = '\0';
	return dst;
}
