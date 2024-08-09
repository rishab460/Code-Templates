class SGTree {
	vector<int> seg;
    int _query(int ind, int low, int high, int l, int r) {
		if (r < low || high < l) return 0;
		if (low >= l && high <= r) return seg[ind];
		int mid = (low + high) >> 1;
		int left = _query(2 * ind + 1, low, mid, l, r);
		int right = _query(2 * ind + 2, mid + 1, high, l, r);
		return left + right;
	}
    void _update(int ind, int low, int high, int i, int val) {
		if (low == high) {
			seg[ind] = val;
			return;
		}
		int mid = (low + high) >> 1;
		if (i <= mid) _update(2 * ind + 1, low, mid, i, val);
		else _update(2 * ind + 2, mid + 1, high, i, val);
		seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
	}
public:
	SGTree(vector<int> &arr) {
        int n = arr.size();
		seg.resize(4 * n + 1);
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
    void update(int i, int val) {
        _update(0, 0, seg.size()/4-1, i, val);
    }
};