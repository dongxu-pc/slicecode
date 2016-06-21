#include <iostream>
//#include <fstream>
//#include <string>

typedef long long int LL;
const int N=100002;
LL A[N];
const int M=41;//enough to store the max number
	
struct trie_node{
	int next[2];
}tree[N*M];
int used_node;

void init_node(int node_id){
	tree[node_id].next[0]=tree[node_id].next[1]=-1;
}

LL max(LL a,LL b){return a>b ? a:b;}

void insert_node(LL new_val){
	int i,node_id=0,id;
	for(i=M-1;i>=0;i--){
		if(new_val&(1LL<<i))
			id=1;
		else
			id=0;
		if(tree[node_id].next[id]==-1){
			init_node(used_node);
			tree[node_id].next[id]=used_node++;
		}
		node_id=tree[node_id].next[id];
	}
}

LL find_max_node(LL suffix_val){
	int i,node_id=0,id;
	LL result=0;
	for(i=M-1;i>=0;i--){
		if(suffix_val&((1LL)<<i)) 
			id=0;
		else
			id=1;
		if(tree[node_id].next[id]==-1)
			id=id^1;
		result=result*2+id;
 		node_id=tree[node_id].next[id];
	}
	return result;
}

int main(void){
	int n,i;
	scanf("%d",&n);
	LL prefix=0,suffix=0,res=0;
	for(i=0;i<n;i++){
		scanf("%lld",&A[i]);
		suffix^=A[i];
	}

	/** for my test case
	std::string testfile;
	std::cin>>testfile;
    std::ifstream in(testfile);
	in>>n;
	for(i=0;i<n;i++){
		in>>A[i];
		suffix^=A[i];
	}
	**/

	init_node(0);
	used_node=1;
	insert_node(0LL);//when the prefix is empty
	for(i=0;i<n;i++){
		prefix^=A[i];
		suffix^=A[i];
		insert_node(prefix);
		res=max(res,find_max_node(suffix)^suffix);
	}
	printf("%lld\n",res);

	return res;
}


