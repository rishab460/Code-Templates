class SGTree {
	vector<int> seg;
    vector<int> lazy;

    int _query(int ind, int low, int high, int l, int r) {
        // update if any updates are remaining 
		// as the node will stay fresh and updated 
		if(lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] += lazy[ind]; 
				lazy[2*ind+2] += lazy[ind]; 
			}

			lazy[ind] = 0; 
		}
		if (r < low || high < l) return 0;
		if (low >= l && high <= r) return seg[ind];
		int mid = (low + high) >> 1;
		int left = _query(2 * ind + 1, low, mid, l, r);
		int right = _query(2 * ind + 2, mid + 1, high, l, r);
		return left + right;
	}
   	void _update(int ind, int low, int high, int l, int r, int val) {
		// update the previous remaining updates 
		// and propogate downwards 
		if(lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] += lazy[ind]; 
				lazy[2*ind+2] += lazy[ind]; 
			}

			lazy[ind] = 0; 
		}

		// no overlap 
		// we don't do anything and return 
		// low high l r or l r low high 
		if(high < l or r < low) {
			return; 
		}

		// complete overlap 
		// l low high r 
		if(low>=l && high <= r) {
			seg[ind] += (high - low + 1) * val; 
			// if a leaf node, it will have childrens
			if(low != high) {
				lazy[2*ind+1] += lazy[ind]; 
				lazy[2*ind+2] += lazy[ind]; 
			}
			return; 
		}
		// last case has to be no overlap case
		int mid = (low + high) >> 1; 
		_update(2*ind+1, low, mid, l, r, val);
		_update(2*ind+2, mid+1, high, l, r, val); 
		seg[ind] = seg[2*ind+1] + seg[2*ind+2]; 
	}
public:
	SGTree(vector<int> &arr) {
        int n = arr.size();
		seg.resize(4 * n + 1);
        lazy.resize(4*n+1);
        build(0, 0, n-1, arr);
	}
	void build(int ind, int low, int high, vector<int> &arr) {
		if (low == high) {
			seg[ind] = arr[low];
			return;
		}
		int mid = (low + high) / 2;
		build(2 * ind + 1, low, mid, arr);
		build(2 * ind + 2, mid + 1, high, arr);
		seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
	}
    int query(int l, int r) {
        return _query(0, 0, seg.size()/4-1, l, r);
    }
    void update(int l, int r, int val) {
		_update(0, 0, seg.size()/4-1, l, r, val);
	}
};