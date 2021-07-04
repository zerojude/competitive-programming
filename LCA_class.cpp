           #include<bits/stdc++.h>
           using namespace std ; 
           #define ar array 
           #define int long long  
           #define ld long double
           #define nl cout<<"\n" 
           


// **************_____LCA_____****************  

/*
  class is implented considering the input is 0 based indexing 
  
  ** if the input is in the 1 based indexing format then provide 1 in the parameter field like ---> t.read(1)

  function implented are  

  read()  // reads all ( N-1 ) edges of tree considering 0 based input
  read(1) // reads all ( N-1 ) edges of tree considering 1 based input // it will manage // 
             after it you should provie 0 based input for all the query stuff

  lca( a , b ) // lca query in O(logn) time 
  len( a , b ) // path length between a to b 
  depth( a )   // depth of node a 
  display()    // prints all the useful information 
*/

// this define is neccessarry 

 #define nl cout<<"\n"  // necessary define 
 class LCA
 {
   
    public:

     int N = 0 , timer = 0 , k = 10;
     
     vector<vector<int>>g ;
     vector<vector<int>>t ;
    
     vector<int>tin;
     vector<int>tout;
     vector<int>dis ;
    

     LCA( int N )
     {
         this->N = N ; 
         k = log2(N)+1;
         timer = 0 ;

         vector<int>temp(N,0);

         tin = temp ;
         tout = temp ;
         dis = temp ;

         vector<vector<int>>temp1(N, vector<int>{} );
         vector<vector<int>>temp2(N, vector<int>(k,0));

         g = temp1;
         t = temp2;
     }

     void dfs( int i , int d , int p )
     {
        for( auto j : g[i] )
        {
             if( j != p )
             {
                 dis[j] = 1 + d ;
                 dfs( j , d+1 , i );
             }
        }
     }



    void lift( int i , int p )
    {
         t[i][0] = p ;
         tin[i] = ++timer;

         for( int j = 1 ; j < k ; j++ )
             t[i][j] = t[t[i][j-1]][j-1];

         for( auto j : g[i] )
         {
             if( j != p )
             lift( j , i );
         }
         
         tout[i] = ++timer;
    }


     void read( int z = 0 )
     {
        for( int i = 0 ; i < N-1 ; i++ )
        {
             int a , b ; 
             cin>>a>>b;
             if( z == 1 )
             {
                 a--;
                 b--;
             }
             g[a].push_back(b) ;
             g[b].push_back(a) ;
        }

        dis[0] = 0 ;
        dfs( 0 , 0 , 0 ) ;
        lift( 0 , 0 ); 
     }



     bool isAncestor( int a , int b )
     {
         if( tin[a] <= tin[b] && tout[a] >= tout[b] )
               return 1 ; 
               return 0 ; 
     }


     int lca( int a , int b )
     {
       
         if( isAncestor( a , b ) )
            return a ;
         if( isAncestor( b , a ) )
            return b ;

         for( int i = k-1 ; i >= 0 ; i-- )
         {
            if( !isAncestor( t[a][i] , b ) )
            {
                 a = t[a][i] ;
            }
         }
         return t[a][0] ;
     }

     int len( int a , int b )
     {
         int l = lca( a , b );
         return dis[a] + dis[b] - 2*dis[l] ;
     }
    
     int depth( int a )
     {
        return dis[a] ;
     }

     void display()
     {

         cout<<"****internal implementation is 0-bases indexing**********";
         nl;
         cout<<"****please be carefull while reading input give 1- when input is in the 1 base indexing ";

         nl;
         nl;
         nl;
         
         cout<<"graph is in the formate a---> p , q , r ";
         nl;
         nl;

         for( int i = 0 ; i < N ; i++ )
         {
            cout<<i+1<<"------->";
            for( int j = 0 ; j < g[i].size() ; j++ )
                cout<<g[i][j]+1<<" ";
             nl;
         }

         nl;
         nl;

         cout<<"lift array";
         nl;

         for( int i = 0 ; i < N ; i++ )
         for( int j = 0 ; j < k ; j++ )
            cout<<t[i][j]<<" \n"[j==k-1];


         
         nl;
         nl;

         cout<<"distance array";
         nl;
         for( auto x : dis )
            cout<<x<<" ";

         nl;
         nl;
     }
 };


// *******************_____LCA____END____*******************



