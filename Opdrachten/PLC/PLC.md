| Stap  | Set                      | Rest                |
|-------|--------------------------|---------------------|
| Q0    | Q10.ini                  | Q1                  |
| Q1    | Q0.st+ a0 + a1           | Q2                  |
| Q2    | Q1.!a0                   | Q3                  |
| Q3    | Q2.a2                    | Q4                  |
| Q4    | Q3.a3                    | Q5                  |
| Q5    | Q4.a4                    | Q6                  |
| Q6    | Q5.(TIM 0000 #4)         | Q7                  |
| Q7    | Q6.a5                    | Q8                  |
| Q8    | Q7.(TIM 0000 #4)         | Q9                  |
| Q9    | Q8.a6                    | Q10                 |
| Q10   | Q9.a7                    | Q0                  |

#### Acties
- **a0** = TIM 0000 #4
- **a1** = 000.07 (_5B8)
- **a2** = 000.06 (_5B7)
- **a3** = 000.01 (_5B2)
- **a4** = 000.00 (_5B1)
- **a5** = 000.02 (_5B3)
- **a6** = 000.03 (_5S4)
- **a7** = 000.04 (_5S5)

#### Stappen
- **Q1** = 001.07 (_5Y8)
- **Q2** = 001.06 (_5Y7)
- **Q3** = 001.00 (_5Y1)
- **Q4** = 001.02 (_5Y3)
- **Q5** = TIM 0001 #4
- **Q6** = 001.01 (_5Y2)
- **Q7** = 001.05 (_5Y6)
- **Q8** = 001.03 (_5Y4)
- **Q9** = 001.04 (_5Y5)
- **Q10** = 2000.15 (LED-15)


#### Beschrijving van de onderdelen.
- **5B1**: Punched lowered and punch pressure achieved
- **5B2**: Changeover position; rapid -> punch
- **5B3**: Punch raised
- **5S4**: Swivel arm in transfer position
- **5S5**: Swivel arm in rear position
- **5B6**: No cover present in transfer position
- **5B7**: Punch slide in punch position
- **5B8**: Magazine slide retracted

- **5Y1**: Punch cylinder to advance
- **5Y2**: Punch cylinder to retract
- **5Y3**: Punch throttle valve
- **5Y4**: Swivel arm to transfer position
- **5Y5**: Swivel arm to rear position
- **5Y6**: Advance slide to transfer position
- **5Y7**: Retract slide to punch position
- **5Y8**: Eject cover from magazine

#### 
- **Q1** = A1
- **Q2** = A2
- **Q3** = A3
- **Q4** = A4
- **Q5** = A5
- **Q6** = A6
- **Q7** = A7
- **Q8** = A8
- **Q9** = A9
- **Q10** = A10                  

![LadderDiagram(LD)](https://github.com/user-attachments/assets/b1c3fdeb-3a8e-46a4-a359-7d4c4096d195)



