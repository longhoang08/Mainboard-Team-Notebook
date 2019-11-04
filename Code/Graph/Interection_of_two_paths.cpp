int intersect(int a, int b, int c, int d){
 if(lca(b,c)!=c) return 0;
 int z = lca(b,d);
 if(lv[c]<lv[a]){
 if(lca(a,z)==a) return dist(z,a);
 	}else{
 if(lca(c,z)==c) return dist(c,z);}
 return 0;
}