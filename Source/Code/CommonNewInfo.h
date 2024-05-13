#include <vector>
//desagrupar itens únicos
static const std::vector<int> allowedItems = { 412, 413, 419, 420, 4010, 4011, 4148, 787, 1764, 1765, 3314, 4026, 4038, 4039, 4900, 4040, 4041, 4042, 4140, 4144, 777, 3173, 3182, 4146, 411, 776, 787, 1764, 1765, 3210, 3336, 3517, 3431, 4097, 4028, 4029, 4026, 4027, 4145, 1739 };

static bool isSplittable(int itemIndex)
{
	if (std::find(allowedItems.begin(), allowedItems.end(), itemIndex) != allowedItems.end())
		return true;
	//desagrupar itens parecidos

	// Joias do poder
	if (itemIndex >= 3200 && itemIndex <= 3209)
		return true;

	// Amagos
	if (itemIndex >= 2390 && itemIndex <= 2419)
		return true;
	
	if (itemIndex >= 3358 && itemIndex <= 3360)
		return true;
	
	if (itemIndex >= 475 && itemIndex <= 489)
		return true;

	if (itemIndex >= 3393 && itemIndex <= 3396)
		return true;

	if (itemIndex >= 3407 && itemIndex <= 3416)
		return true;

	if (itemIndex >= 3324 && itemIndex <= 3326)
		return true;

	if (itemIndex >= 3310 && itemIndex <= 3313)
		return true;

	if (itemIndex >= 3361 && itemIndex <= 3366)
		return true;

	if (itemIndex >= 3386 && itemIndex <= 3389)
		return true;

	if (itemIndex >= 4016 && itemIndex <= 4020)
		return true;

	if (itemIndex >= 2420 && itemIndex <= 2439)
		return true;

	if (itemIndex >= 3319 && itemIndex <= 3321)
		return true;
	return false;
}