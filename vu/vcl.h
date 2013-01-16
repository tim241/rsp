#include "vu.h"

void VCL(int vd, int vs, int vt, int element)
{
    register int i;
    for (i = 0; i < 8; i++)
    {
        int sel = element_index[element][i];
        signed short s1 = VR[vs].s[i];
        signed short s2 = VR[vt].s[sel];
        if (VCF[00] & (0x0001 << i))
        {
            if (VCF[00] & (0x0100 << i))
            {
                VACC[i].w[01] = (VCF[01] & (0x0001 << i))
                              ? -s2 : +s1;
            }
            else
            {
                if (VCF[02] & (0x0001 << i))
                {
                    if (((UINT32)(UINT16)s1 + (UINT32)(UINT16)s2) > 0x10000)
                    { /* proper fix for Harvest Moon 64, r4 */
                        VACC[i].w[01] = s1;
                        VCF[01] &= ~(0x0001 << i);
                    }
                    else
                    {
                        VACC[i].w[01] = -s2;
                        VCF[01] |= 0x0001 << i;
                    }
                }
                else
                {
                    if ((UINT32)(UINT16)s1 + (UINT32)(UINT16)s2)
                    { /* ������ � ������ ��� Harvest Moon 64, */
                        VACC[i].w[01] = s1;
                        VCF[01] &= ~(0x0001 << i);
                    } /* ���� ��������������� pj64 1.4 rsp */
                    else
                    {
                        VACC[i].w[01] = -s2;
                        VCF[01] |= 0x0001 << i;
                    }
                }
            }
        }
        else
        {
            if (VCF[00] & (0x0100 << i))
            {
                if (VCF[01] & (0x0100 << i))
                {
                    VACC[i].w[01] = s2;
                }
                else
                {
                    VACC[i].w[01] = s1;
                }
            }
            else
            {
                const unsigned short flag_offset = 0x0100 << i;
                VACC[i].w[01] = ((INT32)(UINT16)s1 < (INT32)(UINT16)s2)
                              ? s1 : s2;
                VCF[01] = ((INT32)(UINT16)s1 < (INT32)(UINT16)s2)
                        ? VCF[01] & ~flag_offset
                        : VCF[01] | flag_offset;
            }
        }
    }
    VR[vd].s[00] = VACC[00].w[01];
    VR[vd].s[01] = VACC[01].w[01];
    VR[vd].s[02] = VACC[02].w[01];
    VR[vd].s[03] = VACC[03].w[01];
    VR[vd].s[04] = VACC[04].w[01];
    VR[vd].s[05] = VACC[05].w[01];
    VR[vd].s[06] = VACC[06].w[01];
    VR[vd].s[07] = VACC[07].w[01];
    VCF[00] = 0x0000;
    VCF[02] = 0x0000;
    return;
}