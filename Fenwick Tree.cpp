  #include<bits/stdc++.h>
  using namespace std ; 


/********************______Fenwick Tree______******************************/

// note- class is implemented considering the O-based indexing 
// fenwick  Tree ____ update - ____ query // format is followed 
// FT_PR - > point update range query 
// FT_RP - > range update point query
// FT_RR - > range update range query

 // sum();
 // add(); 
 // at(); -> for getting point information about array

/*

 sum() , add() both are addaptive function

 sum(index) - Prefix sum till that index
 sum(l,r) - sum of the range [l,r]

 add(index,val)- point update
 add(l,r,x)- range update



 keep in mind 0-based indexing is followed for building the fenwick tree however interval working uses 1-based indexing

*/
class FT_PR
  {
     public :
     vector<int>T;
     int N ;
     FT_PR( int N )
     {
        this->N = N ; 
        T.assign(N+1,0);
     }
     FT_PR( vector<int>&A ):FT_PR(A.size())
     {
       for( int i = 0 ; i < N ; i++ )
       {
         add(i,A[i]);
       }
     }
     void add( int k , int val )
     {  
        k++ ; 

        while( k <= N )
        {
           T[k] += val;
           k += k&-k ; 
        }
     }
     int sum( int k )
     {
        int s = 0 ;
        k++;

        while( k >= 1 )
        {
            s += T[k];
            k -= k&-k;
        } 
        return s ; 
     }
     int sum(int l, int r)
     {
        return sum(r)-sum(l-1);
     }
     int at(int k)
     {
        return sum(k,k);
     }
  };
 


  class FT_RP
  {
     public :
      
      int N ; vector<int>T ;
      FT_RP(int N)
      {
         this->N = N ;
         T.assign(N+1,0);
      }

      FT_RP(vector<int>&A):FT_RP(A.size())
      {
         for( int i = 0 ; i < N ; i++ )
            add(i,i,A[i]);
      }

      void add( int k , int val)
      {
         k++;
         while(k<=N)
         {
            T[k] += val;
            k += k&-k ; 
         }
      }

      void add( int l , int r , int val )
      {
          add(l,val);
          add(r+1,-val);
      }

      int at( int k )
      {
         int s = 0 ; 
         k++;
         while( k >= 1 )
         {
            s += T[k] ;
            k -= k&-k ;
         }
         return s ;
      }
  };


   class FT_RR
   {
     public :
     
      int N ;
      vector<int>T1 , T2 ;

      FT_RR(int N )
      {
         this->N = N ; 
         T1.assign(N+1,0);
         T2.assign(N+1,0);
      }

      FT_RR(vector<int>&A):FT_RR(A.size())
      {
          for( int i = 0 ; i < N ; i++ )
          {
            add( i , i , A[i] );
          }
      }

      void add( int k , vector<int>&T , int val )
      {
         k++;
         while( k <= N )
         {
            T[k] += val;
            k += k&-k;
         }
      }

      void add( int l , int r , int val )
      {
         add(l,T1,val);
         add(r+1,T1,-val);

         add(l,T2,val*(l-1));
         add(r+1,T2,-val*r);
      }

      int sum( int k , vector<int>&T )
      {
         k++;
         int s = 0 ; 

         while( k >= 1 )
         {
            s += T[k] ;
            k -= k&-k;
         }
         return s ;
      }

      int sum( int k )
      {
         return sum(k,T1)*k - sum(k,T2);
      }
      

      int sum(int l , int r )
      {
         return sum(r) - sum(l-1);
      }

      int at( int k )
      {
         return sum(k,k);
      }

   };