#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

void bars_and_stars(int bars, int stars, int current_values[], int current_node, int num_nodes, int resource_combos[][num_nodes]);
int nChoosek(int n, int k);

struct defender {
	int resources;
	int payoff[50];
};

struct attacker {
	int resources;
	int payoff[50];
};
struct attacker *ap;

struct p_node {
	int hitpoints;
	int connect[50];
};
struct p_node *pp;

int r_combos_index = 0;

int main(int argc, char* argv[]){
	int cyber_nodes, physical_nodes, attackers, players;

	printf("How many cyber nodes (50 maximum)?");
	scanf("%d", &cyber_nodes);
	if(cyber_nodes>50){
		printf("Number out of range\nExiting...\n");
		return 0;
	}
	printf("How many physical nodes (50 maximum)?");
	scanf("%d", &physical_nodes);
	if(physical_nodes>50){
		printf("Number out of range\nExiting...\n");
		return 0;
	}
	printf("How many attackers?");
	scanf("%d", &attackers);
	players = attackers + 1;

	//initialize physical nodes
	pp= (struct p_node*) malloc(physical_nodes * sizeof(struct p_node));
	for(int i=0; i<physical_nodes; i++){
		printf("======================================================\n");
		printf("Please enter connectivity matrix of %d digits for the physical node #%d\n", cyber_nodes, i);
		printf("An entry of 1 represents a connection while 0 represents no connection\n");
		for(int j=0; j<cyber_nodes; j++){
			printf("Does physical node %d connect with cyber node %d (1 or 0)", i, j);
			scanf("%d", &pp[i].connect[j]);
		}
		printf("Please enter how many connected cyber nodes must fail for physical node #%d to fail\n", i);
		scanf("%d", &pp[i].hitpoints);
	}

	//initialize attackers
	ap = (struct attacker*) malloc(attackers * sizeof(struct attacker));
	for(int i=0; i<attackers; i++){
		printf("======================================================\n");
		printf("Please enter how many resources attacker #%d will have\n", i);
		scanf("%d", &ap[i].resources);
		printf("Please enter the cost/payoff of all %d physical nodes to attacker #%d\n", physical_nodes, i);
		printf("Enter a value between 0 and 100 to represent how much each attack values each physical node'\n");
		for (int j=0; j<physical_nodes; j++){
			printf("How much does attacker %i value physical node %i (0 to 100)\n", i, j);
			scanf("%d", &ap[i].payoff[j]);
		}
	}


	//initialize defender
	struct defender d1;
	printf("==============================================================\n");
	printf("Please enter how many resources the defender will have\n");
	scanf("%d", &d1.resources);
	printf("Please enter the cost/payoff of all %d physical nodes to the defender\n", physical_nodes);
	printf("Enter a value between 0 and 100 to represent how much the defender values each physical node\n");
	for (int i=0; i<physical_nodes; i++){
		printf("How much does the defender value physical node %i (0 to 100)\n", i);
		scanf("%d", &d1.payoff[i]);
	}


	//Player Stats
	printf("============================Player Stats==============================\n");
	printf("There will be %i attackers and 1 defender\n", attackers);
	printf("Defender stats:\n\tdefender has %i resources\n", d1.resources);
	for(int i=0; i<physical_nodes; i++){
		printf("\tphysical node %i value to defender: %i\n", i, d1.payoff[i]);
	}
	for(int i=0; i<attackers; i++){
		printf("\nAttacker #%d stats:\n\tattacker has %i resources\n", i, ap[i].resources);
		for(int j=0; j<physical_nodes; j++){
			printf("\tphysical node %i value to attacker: %i\n", j, ap[i].payoff[j]);
		}
	}

	//Node Stats
	printf("============================Node Stats================================\n");
	printf("There will be %d cyber nodes and %d physical nodes\n", cyber_nodes, physical_nodes);
	for(int i=0; i<physical_nodes; i++){
		printf("\nPhysical Nodes #%d stats:\n\tphysical node will fall after %i connected cyber nodes fall\n", i, pp[i].hitpoints);
		for(int j=0; j<cyber_nodes; j++){
			if(pp[i].connect[j] == 1) {
				printf("\tphysical node is connected to cyber node %i\n", j);
			}
		}
	}

	//Finding array size
	int totalcombos=0;
	for(int i=0; i<attackers; i++){
		int resources=ap[i].resources;
                int num_combos=nChoosek(resources + cyber_nodes - 1, resources);
		totalcombos+=num_combos;
	}
	totalcombos+=nChoosek(d1.resources + cyber_nodes - 1, d1.resources);

	//declares matrices for values
	int combo_matrix[totalcombos][cyber_nodes];
	int connect_matrix[(50*physical_nodes)];
	int cost_matrix[(50*players)];
	int hitpoint_matrix[(physical_nodes)];
	int total_combos=0;

	//pushes values into the cost and combo matrices
	for(int i=0; i<attackers; i++){
		int resources=ap[i].resources;
        	int num_combos=nChoosek(resources + cyber_nodes - 1, resources);
		int resource_combos[num_combos][cyber_nodes];
        	int temp_values[cyber_nodes];
        	for (int j=0; j<cyber_nodes; j++){
                	temp_values[j] = -1;
        	}
		bars_and_stars(cyber_nodes - 1, resources, temp_values, 0, cyber_nodes, resource_combos);
		printf("Attacker #%i Resource Combinations:\n", i);
		for (int j=0; j<num_combos; j++){
			for (int k=0; k<cyber_nodes; k++){
				combo_matrix[(total_combos+j)][k]=resource_combos[j][k];
				printf("%i", resource_combos[j][k]);
			}
			printf("\n");
		}
		printf("===============================\n");
		total_combos+=num_combos;
		r_combos_index=0;
		//return the combination matrices into an array that holds all the combination matrices
		for(int j=0; j<50; j++){
			cost_matrix[((50*i)+j)]=ap[i].payoff[j];
		}
	}
	int num_combos=nChoosek(d1.resources + cyber_nodes - 1, d1.resources);
        int resource_combos[num_combos][cyber_nodes];
        int temp_values[cyber_nodes];
        for (int j=0; j<cyber_nodes; j++)
        {
        	temp_values[j] = -1;
        }
	bars_and_stars(cyber_nodes - 1, d1.resources, temp_values, 0, cyber_nodes, resource_combos);
	printf("Defender Resource Combinations:\n");
	for (int i=0; i<num_combos; i++)
	{
		for (int j=0; j<cyber_nodes; j++)
		{
			combo_matrix[(total_combos+i)][j]=resource_combos[i][j];
			printf("%i", resource_combos[i][j]);
		}
		printf("\n");
	}
	printf("==================================\n");
	total_combos+=num_combos;
	for(int i=0; i<50; i++){
		cost_matrix[((50*attackers)+i)]=d1.payoff[i];
	}


	//pushes values into the hitpoint and connect matrices
	for(int i=0; i<physical_nodes; i++){
		hitpoint_matrix[i]=pp[i].hitpoints;
		for(int j=0; j<50; j++){
			connect_matrix[((50*i)+j)]=pp[i].connect[j];
		}
	}

	//Frees up Allocated Memory Space
	if(ap)	{
		free(ap);
		printf("\nAttacker Memory Deallocated :)\n");
	}

	if(pp)	{
		free(pp);
		printf("\nPhysical Node Memory Deallocated :)\n");
	}
	/*for (int i=0; i<total_combos; i++)
	{
		printf("Resource Combo %i: ", i);
		for (int j=0; j<cyber_nodes; j++)
		{
			printf("%i", resource_combos[i][j]);
		}
		printf("\n");
	}*/
}


int gamebuild(int c_nodes, int p_nodes, int players, int connect_m, int cost_m, int hitpoint_m) {

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
