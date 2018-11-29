class query{
public:
	int x, y, id, type;
	void next_x(){
		if(type==1) x+=x&-x;
		else x-=x&-x;
	}
	void next_y(){
		if(type==1) y+=y&-y;
		else y-=y&-y;
	}
};
const int maxqsize=100000;
vector <query> q;
deque <int> start[maxqsize+1];
vector <query> temp[n+1];
class node{
public:
	int value, y;
	int next, prev;
	node(int y){
		this->y=y;
		value=0;
		next=prev=-1;
	}
};
vector <node> ft[n+1];
int done[n+1];
int pos[n+1];
int main() {
	// your code goes here
	for(query a: q){
		while((a.x)&&(a.x<=n)){
			temp[a.x].pb(a);
			a.next_x();
		}
	}
	FOR(i, 1, n){
		for(query a: temp[i]){
			while((a.y)&&(a.y<=n)){
				if(done[a.y]!=i){
					done[a.y]=i;
					pos[a.y]=ft[i].size();
					ft[i].pb(node(a.y));
				}
				a.next_y();
			}
		}
		for(node &a: ft[i]){
			int yy=a.y+(a.y&(-a.y));
			if(yy<=n){
				if(done[yy]==i) a.next=pos[yy];
			}
			yy=a.y-(a.y&(-a.y));
			if(done[yy]==i) a.prev=pos[yy];
		}
		for(query a: temp[i]){
			if(a.type==1)///up
				start[a.id].pb(pos[a.y]);
			else start[a.id].push_front(pos[a.y]);
		}
	}
	return 0;
 
}