#ifndef __TEST_DR_PYTHAGORE_H__
#define __TEST_DR_PYTHAGORE_H__

void inc_ok();
void inc_nok();
#define ASSERT(a) if (a) {                          \
    inc_ok();                                       \
    cout << "  \x1b[32;1m<OK>\x1b[0m : " #a << endl;}  \
else {                                              \
    inc_nok();                                      \
    cout << "  \x1b[31;1m<NOK>\x1b[0m: " #a << endl;}
void finalize();

#endif /* __TEST_DR_PYTHAGORE_H__ */

