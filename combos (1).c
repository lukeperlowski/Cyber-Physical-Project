#include <stdio.h>
#include <string.h>

void bars_and_stars(int bars, int stars, int current_values[], int current_node, int num_nodes, int resource_combos[][num_nodes]);
int nChoosek(int n, int k);
void main();

int r_combos_index = 0;

void main()
{
	int num_nodes = 3;
	int resources = 4;
	int num_combos = nChoosek(resources + num_nodes - 1, resources);
	int resource_combos[num_combos][num_nodes];
	int temp_values[num_nodes];
	for (int i = 0; i < num_nodes; i++)
	{
		temp_values[i] = -1;
	}

	bars_and_stars(num_nodes - 1, resources, temp_values, 0, num_nodes, resource_combos);
	for (int i = 0; i < num_combos; i++)
	{
		printf("Resource Combo %i: ", i);
		for (int j = 0; j < num_nodes; j++)
		{
			printf("%i", resource_combos[i][j]);
		}
		printf("\n");
	}
}

void bars_and_stars(int bars, int stars, int temp_values[], int current_node, int num_nodes, int resource_combos[][num_nodes])
{
	if (stars == 0)
	{
		if (current_node < num_nodes)
		{
			for (int i = current_node; i < num_nodes; i++)
			{
				temp_values[i] = 0;
			}
		}
		for(int i = 0; i < num_nodes; i++)
		{
			resource_combos[r_combos_index][i] = temp_values[i];
		}
		r_combos_index++;
		return;
	}

	if (bars == 0)
	{
		temp_values[current_node] = stars;
		for (int i = 0; i < num_nodes; i++)
		{
			resource_combos[r_combos_index][i] = temp_values[i];
		}
		r_combos_index++;
		return;
	}

	for(int i = 0; i <= stars; i++)
	{
		temp_values[current_node] = i;
		bars_and_stars(bars-1, stars-i, temp_values, current_node + 1, num_nodes, resource_combos);
	}
}

int nChoosek(int n, int k)
{
	if (k > n)
	{
		return 0;
	}

	if (k == 0)
	{
		return 1;
	}

	return nChoosek(n - 1, k) + nChoosek(n - 1, k - 1);
}