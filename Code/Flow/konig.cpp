void konig(){
   queue<int> qu;
   f1(i,m) if (!Assigned[i]) qu.push(i);
   f1(i,n) if (!Assigned[N-i]) qu.push(N-i);
   while (qu.size()){
      int u=qu.front(); qu.pop();
      for (int i=0; int v=a[u][i]; i++)
      if (!(Choosed[v]++)) qu.push(Assigned[v]);
   }
   f1(i,m) if (Assigned[i] && !Choosed[i] && !Choosed[Assigned[i]]) 
   Choosed[i]=true;
}