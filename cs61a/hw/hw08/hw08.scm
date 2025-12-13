(define (ascending? s)    
(
        if(or (null? s) (null? (cdr s)))
        #t
        (
            if
            (<= (car s) (car (cdr s))) ;无内置的cadr函数
            (ascending? (cdr s))
            #f
        )
)
)

(define (my-filter pred s)
  (define (helper pred s result)
    (if (null? s)
        (cdr result)
        (if (pred (car s))
            (helper pred (cdr s) (append result (list (car s))))
            (helper pred (cdr s) result))))
  (helper pred s '(1)))

(define (interleave lst1 lst2) 

    (define(helper lst1 lst2 result)
    (
        if (and ( > (length lst1) 0) ( > (length lst2) 0))
        (helper lst2 (cdr lst1) (append result (list (car lst1))))
        (if ( = (length lst1) 0)
        (cdr (append result lst2))
        (cdr (append result lst1))
        )
    ))
(helper lst1 lst2 '(1))

)



(define (member item lst)
  (cond ((null? lst) #f)
        ((equal? item (car lst)) lst)
        (else (member item (cdr lst)))))

(define (no-repeats s) 
    (define (helper s result)
    (if (null? s)
    (cdr result)
    (
        if 
    (member (car s) result)
    (helper (cdr s) result)
    (helper (cdr s) (append result (list (car s))))
    
    )))

    (helper s '(-1))
)
