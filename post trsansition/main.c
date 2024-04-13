#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char *id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package *packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char *name;
	post_office *offices;
	int offices_count;
};

typedef struct town town;

void print_all_packages(town t)
{
	printf("%s:\n", t.name);
	int officeCount = t.offices_count;

	for (int i = 0; i < officeCount; i++)
	{
		int packageCount = t.offices[i].packages_count;
		printf("\t%d:\n", i);
		for (int j = 0; j < packageCount; j++)
		{
			char *id = t.offices[i].packages[j].id;
			printf("\t\t%s\n", id);
		}
	}
}

void send_all_acceptable_packages(town *source, int source_office_index, town *target, int target_office_index)
{
	int minWeight = target->offices[target_office_index].min_weight;
	int maxWeight = target->offices[target_office_index].max_weight;

	for (int i = 0; i < source->offices[source_office_index].packages_count;)
	{
		package currentPackage = source->offices[source_office_index].packages[i];
		if (minWeight <= currentPackage.weight && currentPackage.weight <= maxWeight)
		{
			target->offices[target_office_index].packages_count++;
			target->offices[target_office_index].packages = (package*)realloc(target->offices[target_office_index].packages, target->offices[target_office_index].packages_count * sizeof(package));

			target->offices[target_office_index].packages[target->offices[target_office_index].packages_count - 1] = currentPackage;

			for (int j = i; j < source->offices[source_office_index].packages_count - 1; j++)
			{
				source->offices[source_office_index].packages[j] = source->offices[source_office_index].packages[j + 1];
			}
			source->offices[source_office_index].packages_count--;
		}
		else
		{
			i++;
		}
	}
}

int total_packages_in_town(town current)
{
	int total_packages = 0;
	for (int i = 0; i < current.offices_count; i++)
	{
		post_office *office = &current.offices[i];
		total_packages += office->packages_count;
	}
	return total_packages;
}

town town_with_most_packages(town *towns, int towns_count)
{
	town mostPackages = towns[0];
	int maxPackagesCount = total_packages_in_town(towns[0]);

	for (int i = 1; i < towns_count; i++)
	{
		int currentPackagesCount = total_packages_in_town(towns[i]);
		if (currentPackagesCount > maxPackagesCount)
		{
			maxPackagesCount = currentPackagesCount;
			mostPackages = towns[i];
		}
	}
	return mostPackages;
}

town *find_town(town *towns, int towns_count, char *name)
{
	for (int i = 0; i < towns_count; i++)
	{
		if (strcmp(towns[i].name, name) == 0)
		{
			return &towns[i];
		}
	}
	return NULL;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town *towns = malloc(sizeof(town) * towns_count);
	for (int i = 0; i < towns_count; i++)
	{
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office) * towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++)
		{
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package) * towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++)
			{
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--)
	{
		int type;
		scanf("%d", &type);
		switch (type)
		{
		case 1:
			scanf("%s", town_name);
			town *t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town *source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town *target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}
