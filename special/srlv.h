void SRLV(int rs, int rt, int rd, int unused_sa)
{
    unused_sa = 0;
    if (rd == 0)
    {
        message("SRLV\nTried to overwrite $zero.", 0);
        return;
    }
    SR[rd] = (unsigned)SR[rt] >> (SR[rs] & 31);
    return;
}
