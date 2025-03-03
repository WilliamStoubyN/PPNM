class vector{
    double[] data;
    int size => data.Length;
    double this[int i]{  //indexer
        get => data[i];         //accessor
        set => data[i]=value;   //mutator
    }

    vector(int n) {      //constructor
        data = new double[n]
    }

    vector& operator=(const vector&) = default;     //copy assignment
    vector& operator=(vector&&) = default;          //move assignment
    vector& operator+=(const vector&);
}