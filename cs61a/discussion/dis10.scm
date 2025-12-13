;;; Return whether there are n perfect squares with no repeats that sum to total
;;;
;;; scm> (fit 10 2)
;;; #t
;;; scm> (fit 9 2)
;;; #f
(define (fit total n)
    (define (f total n k)
        (
            if (and (= n 0) (= total 0))
                #t
            (if (< total (* k k))
                #f
                (or (f total n (+ k 1)) (f (- total (* k k)) (- n 1) k))
            )
        )
    )
    (f total n 1))

(expect (fit 10 2) #t)  ; 1*1 + 3*3
(expect (fit 9 1)  #t)  ; 3*3
(expect (fit 9 2)  #f)  ;
(expect (fit 9 3)  #f)  ; 1*1 + 2*2 + 2*2 doesn't count because of repeated 2*2
(expect (fit 25 1)  #t) ; 5*5
(expect (fit 25 2)  #t) ; 3*3 + 4*4


(define with-list
        (list
            '(a b) 'c 'd '(e)
        )
    )
    ; (draw with-list)  ; Uncomment this line to draw with-list


(define with-quote
        '(
            (a b) c d (e)
        )
    )
    ; (draw with-quote)  ; Uncomment this line to draw with-quote

(define first
    (cons 'a (cons 'b nil)))


(define with-cons
        (cons
            first (cons 'c (cons 'd (cons '(e) '())))
        )
    )
    ; (draw with-cons)  ; Uncomment this line to draw with-cons


;;; Return a list with all numbers equal to x removed
;;;
;;; scm> (remove '(3 4 3 4 4 3) 3)
;;; (4 4 4)
;;; scm> (remove '(3 4 3 4 4 3) 4)
;;; (3 3 3)


(define (remove s x)
  (if (null? s) nil
    (if (equal? x (car s)) (remove (cdr s) x) (con (car s) (remove (cdr s) x)))
)
)

(expect (remove '(3 4 3 4 4 3) 3) (4 4 4))
(expect (remove '(3 4 3 4 4 3) 4) (3 3 3))

;;; Return a list of pairs containing the elements of s.
;;;
;;; scm> (pair-up '(3 4 5 6 7 8))
;;; ((3 4) (5 6) (7 8))
;;; scm> (pair-up '(3 4 5 6 7 8 9))
;;; ((3 4) (5 6) (7 8 9))
(define (pair-up s)
    (if (<= (length s) 3)
        (cons s nil)
        (cons (cons (car s) (cons (car (cdr s)) '())) (pair-up (cdr(cdr s))))        
    )
)

(expect (pair-up '(3 4 5 6 7 8)) ((3 4) (5 6) (7 8)) )
(expect (pair-up '(3 4 5 6 7 8 9)) ((3 4) (5 6) (7 8 9)) )




(define (up n)
    (define (helper n result)
        (define first (remainder n 10))  ; Using first will shorten your code
        (if (zero? n) result
            (helper
                (quotient n 10)
                if(or (< first (car result)) (equal? result nil))
                    (cons first (cons result nil))
                    (cons first (result))
                )
        )
    )
    (helper
      (quotient n 10)
      nil
    )
)

(expect (up 314152667899) (3 (1 4 (1 5 (2 6 (6 7 8 9 (9)))))))
