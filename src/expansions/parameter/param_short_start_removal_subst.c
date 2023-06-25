#include "lib_str.h"

// @enum ShortestSubstringRemovalFromBeginning
const char *param_short_start_removal_subst(const char *const subst, const char *const removal)
{
	if (!subst)
		return NULL;
	if (!removal)
		return ft_strdup(subst);

	const size_t removal_length = ft_strlen(removal);
	if (ft_strncmp(subst, removal, removal_length) != SAME_STR)
		return ft_strdup(subst);

	return ft_strdup(&subst[removal_length]);
}
