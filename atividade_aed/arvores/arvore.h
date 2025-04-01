    typedef struct arv Arv;

    Arv* arv_criavazia();

    Arv* arv_cria(char c, Arv* e, Arv* d);

    int arv_vazia(Arv* a);

    int arv_pertence(Arv* a, char c);

    Arv* arv_libera(Arv* a);

    void arv_imprime(Arv* a);
