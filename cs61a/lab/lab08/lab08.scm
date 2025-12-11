(define (over-or-under num1 num2) 
  (cond 
    (( > num1 num2) 1 )
    ((< num1 num2) -1)
    (else 0)
  )
  ;;(if(> num1 num2)
  ;;1
  ;;(if (< num1 num2)
  ;;  -1
  ;;  0
  ;;)
  ;;)
)

(define (make-adder num)
  (
    lambda (inc) (+ inc  num);scheme是前缀式写法
  )
)

(define (composed f g) 
  (
    lambda(x)(f (g x))
  )
)

(define (repeat f n) 
(cond
    ((= n 1) f)                 ; n=1 直接返回 f
    (else (lambda (x) (f ((repeat f (- n 1)) x))))
) ; 递归构造合成函数
)


(define (max a b)
  (if (> a b)
      a
      b)
)

(define (min a b)
  (if (> a b)
      b
      a)
)

(define (gcd a b)
(
  if
  (
    zero? (modulo (max a b) (min a b))
  )
  (min a b)
  (gcd b (modulo (max a b) (min a b)))
)
)

