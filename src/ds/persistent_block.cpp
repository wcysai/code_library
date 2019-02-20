constexpr int BLOCK = 800;
typedef vector<int> vi;
typedef shared_ptr<vi> pvi;
typedef shared_ptr<const vi> pcvi;

struct block {
    pcvi data;
    LL sum; 
    
    // add information to maintain 
    block(pcvi ptr) : 
        data(ptr), 
        sum(accumulate(ptr->begin(), ptr->end(), 0ll))
    { }
    
    void merge(const block& another) {
        pvi temp = make_shared<vi>(data->begin(), data->end());
        temp->insert(temp->end(), another.data->begin(), another.data->end());
        *this = block(temp);
    }

    block split(int pos) {
        block result(make_shared<vi>(data->begin() + pos, data->end()));
        *this = block(make_shared<vi>(data->begin(), data->begin() + pos));
        return result;
    }
};

typedef list<block>::iterator lit;

struct blocklist {
    list<block> blk;

    void maintain() {
        lit it = blk.begin();
        while (it != blk.end() and next(it) != blk.end()) {
            lit it2 = it;
            while (next(it2) != blk.end() and 
                     it2->data->size() + next(it2)->data->size() <= BLOCK) {
                it2->merge(*next(it2));
                blk.erase(next(it2));
            }
            ++it;
        }
    }

    lit split(int pos) {
        for (lit it = blk.begin(); ; it++) {
            if (pos == 0) return it;
            while (it->data->size() > pos) {
                blk.insert(next(it), it->split(pos));
            }
            pos -= it->data->size();
        }
    }
    
    LL sum(int l, int r) { // traverse
        lit it1 = split(l), it2 = split(r);
        LL res = 0;
        while (it1 != it2) {
            res += it1->sum;
            it1++;
        }
        maintain();
        return res;
    }
};
