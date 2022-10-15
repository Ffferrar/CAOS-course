   .text      
   .global solve

              
solve:           

    mov    w4, w0
    mov    w0, -1
    mov    w5, 10     
  LoopBegin:         
    cmp    w5, #0       
    beq    LoopEnd 
    
    add    w0, w0, 1  
    
    mov    w5, 1 
    mov    w6, 1
    mov    w7, 1
    
    mul    w5, w5, w4
    mul    w5, w5, w0
    mul    w5, w5, w0
    mul    w5, w5, w0
    
    mul    w6, w6, w1
    mul    w6, w6, w0
    mul    w6, w6, w0
    
    mul    w7, w7, w2
    mul    w7, w7, w0
    
    add    w5, w5, w6
    add    w5 ,w5, w7
    add    w5, w5, w3
    
    
    b      LoopBegin
  LoopEnd:
    
    bgt       solve
    
    ret
