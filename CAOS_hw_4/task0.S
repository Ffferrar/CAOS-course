    .data             
    .global R           
R:      
	.space 8, 0        
	
    .extern A           
    .extern B           
    .extern C
    .extern D

    .text
    .global calculate

calculate:   
    adr x0, A 		    
    ldr x1, [x0]		

    adr x0, B           
    ldr x2, [x0]

    adr x0, C          
    ldr x3, [x0]

    adr x0, D          
    ldr x4, [x0]

    mul x1, x1, x2     
    mul x3, x3, x4      
    add x1, x1, x3     	

    adr x0, R          
	str x1, [x0]        

	ret
