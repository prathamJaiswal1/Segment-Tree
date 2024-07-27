// i m so lazy! you?⟪😎🚀⟫
#define ll long long
class lazy_seg_tree{
    public:
    vector<ll>lazy,seg;
    lazy_seg_tree(int n){
        lazy.resize(4*n+1);
        seg.resize(4*n+1);
    }

    // build the segment tree
    void build(int node,int low,int high,vector<int>&arr){
        //  base case 
        if(low==high){
            seg[node]=arr[low];
            return;
        }
        int left=2*node+1,right=2*node+2;
        int mid=(low+high)>>1;
        // build left child
        build(left,low,mid,arr);
        build(right,mid+1,high,arr);
        seg[node]=seg[left]+seg[right];
    }

    // lazy update  || range update
    // update the previous remaining updates at node
    // complete overlap -> update the node and propagate his child(if exist)
    void update(int node,int low,int high,int qs,int qe,int val){
         int left=2*node+1,right=2*node+2;
        // update previous remaining
        if(lazy[node] != 0){
            seg[node]+=((high-low+1)*lazy[node]);
            if(low != high){
                lazy[left]+=lazy[node];
                lazy[right]+=lazy[node];
            }
            lazy[node]=0;
        }

        // no overlap
        if(low>qe || high<qs){
            return ;
        }

        // complete overlap
        if(low>=qs && high<=qe){
            seg[node]+=((high-low+1)*val);
            if(low != high){
                lazy[left]+=val;
                lazy[right]+=val;
            }
            return ;
        }

        // complete overlap

        int mid=(low+high)>>1;
        update(left,low,mid,qs,qe,val);
        update(right,mid+1,high,qs,qe,val);
        seg[node]=left+right;
    }

    // query 0 indexing based query
    ll query(int node,int low,int high,int qs,int qe){
        int left=2*node+1,right=2*node+2;
         /*If the node is lazy, update it*/
         if(lazy[node] != 0){
            seg[node]+=((high-low+1)*lazy[node]);
            if(low != high){
                lazy[left]+=lazy[node];
                lazy[right]+=lazy[node];
            }
            lazy[node]=0;
         }

         if(qs > high || qe < low){
            return 0;
         }
          
         if(low>=qs && high<=qe){
            return seg[node];
         }

         int mid=(low+high)>>1;
         ll baye=query(left,low,mid,qs,qe);
         ll daye=query(right,mid+1,high,qs,qe);
         return baye+daye;  // u can laugh
    }
};