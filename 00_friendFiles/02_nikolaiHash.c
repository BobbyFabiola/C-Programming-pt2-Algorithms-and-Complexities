int hash(unsigned char A){
    int i;
    unsigned char mask;
    for(i = 0, mask = 1 << 7; mask > 0 && ((A & mask) == 0); i++, mask >>= 1){}

    return i;
}