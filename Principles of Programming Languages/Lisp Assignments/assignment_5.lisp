; Problem 1
; If N is any positive integer and L is any list, then (INDEX N L) returns 
; the Nth element of L if N does not exceed the length of L; if N exceeds 
; the length of the list L, then (INDEX N L) returns the symbol ERROR. 
; For example, (INDEX 3'(A S (A S) (A) D)) => (AS) 
;              (INDEX 6'(A S (A S) (A) D)) => ERROR 
; Note that the first argument of INDEX may be 1, and that the second 
; argument may be NIL.

(defun index (n L)
  (cond ((endp L) 'ERROR)
        ((eql n 1) (car L))
        (T (index (- n 1) (cdr L)))))

; (print (index 3 '(A S (A S) (A) D)))

; Problem 2
; if L is any nonempty list of real numbers then (MIN-FIRST L) is 
; a list whose CAR is the minimum of the numbers in L and whose CDR 
; is the list obtained when the first occurrence of that value is 
; removed from L. (Thus (MIN-FIRST L) is "L with the first occurrence 
; of its minimum value moved to the front".) 
; For example, (MIN-FIRST'(0 3 1 1 0 3 5)) => (0 3 1 1 0 3 5)
;              (MIN-FIRST '(4 3 1 1 0 3 5 0 3 0 2)) => (0 4 3 1 1 3 5 0 3 0 2)
; Note that the argument of MIN-FIRST may be a list of length 1.

(defun min-first(L)
  (if (endp (cdr L))
      L
      (let ((x (min-first (cdr L))))
           (if (<= (car L) (car x))
               L
               (cons (car x)
           (cons (car L) (cdr x)))))))

; (print (MIN-FIRST '(4 3 1 1 0 3 5 0 3 0 2)))

; Problem 3
; if L is any list of real numbers then (SSORT L) is a list of 
; those numbers in ascending order.

(defun ssort (L)
  (if (endp L)
      nil
      (let ((x (min-first L)))
           (cons (car x) (ssort (cdr x))))))

; (print (ssort '(4 9 3 1 11 0 2 7 10 8)))

; Problem 4
; Use the function PARTITION from Lisp Assignment 4 to complete the 
; following definition of a recursive function QSORT such that if L is a 
; list of real numbers then (QSORT L) is a list of those numbers in 
; ascending order.

(defun qsort (L)
  (if (endp L)
       nil 
      (let ((x (partition L (car L))))
                (cond ((endp (car x)) (cons (car L) (qsort (cdr L))))
                      (T (append (qsort (car X)) (qsort (cadr X))))))))

(defun partition (L P)
  (if (endp L)
    '(nil nil)
    (let ((X (partition (cdr L) P)))
      (if (< (car L) P)
        (list (cons (car L) (car X)) (cadr X))
        (list (car X) (cons (car L) (cadr X)))))))

; (print (qsort '(4 9 3 1 0 2 7 10 8)))

; Problem 5
; Define a Lisp function MERGE-LISTS such that if each of L1 and L2 is a 
; list of real numbers in ascending order then (MERGE-LISTS L1 L2) returns
; the list of numbers in ascending order that is obtained by merging L1 
; and L2. Your definition must not call any sorting function. 
; Examples: (MERGE-LISTS '(2 4 5 5 7 8 9)' (3 4 6 9 9)) => (2 3 4 4 5 5 6 7 8 9 9 9)
;           (MERGE-LISTS '(1 2 3) '(4 5 6 7)) => (1 2 3 4 5 6 7) 
;           (MERGE-LISTS '(3 4 5 6 7) '(0 1 2 3)) => (0 1 2 3 3 4 5 6 7)

(defun merge-lists(L1 L2)
      (cond ((endp L1) L2)
            ((endp L2) L1)
            ((< (car L1) (car L2)) (cons (car L1) (merge-lists (cdr L1) L2)))
            (T (cons (car L2) (merge-lists L1 (cdr L2))))))

; (print (MERGE-LISTS '(2 4 5 5 7 8 9)' (3 4 6 9 9)))

; Problem 6
; Use the function SPLIT-LIST from Lisp Assignment 4 and MERGE-LISTS to 
; define a recursive Lisp function MSORT such that if L is a list of real 
; numbers then (MSORT L) is a list consisting of the elements of L in 
; ascending order. In the definition of MSORT you may call SPLIT-LIST, 
; MSORT itself, MERGE-LISTS, CAR, CDR, CADR and ENDP, but you should not 
; call any other function. Be sure to use LET or LET*, so that MSORT only 
; calls SPLIT-LIST once.

(defun msort (L)
      (cond ((endp L) ())
            ((endp (cdr L)) L)
            (T (let ((x (split-list L)))
                    (merge-lists (msort (car x)) (msort (cadr x)))))))

(defun split-list (L)
  (if (endp L)
    '(nil nil)
    (let ((X (split-list (cdr L))))
      (list (cons (car L) (cadr X)) (car X)))))

; (print (msort '(4 9 3 1 0 2 7 10 8)))

; Problem 7
; Do exercise 10.4(a) on page 418 of Sethi, but use Common Lisp instead of 
; Scheme. Name your function REMOVE-ADJ-DUPL.

(defun remove-adj-dupl (L)
  (cond ((or (endp L) (endp (cdr L))) L)
        ((eql (car L) (cadr L)) (cons (car L) (cdr (remove-adj-dupl (cdr L)))))
        (T (cons (car L) (remove-adj-dupl (cdr L))))))

; (print (remove-adj-dupl '(a b a a a c c)))

; Problem 8
; Do exercise 10.4(b) on the same page in Common Lisp. Name your function 
; UNREPEATED-ELTS.

(defun unrepeated-elts (L)
  (cond ((endp L) nil)
        ((or (endp (cdr L)) (not (eql (car L) (cadr L)))) (cons (car L) 
          (unrepeated-elts (cdr L))))
        ((or (endp (cddr L)) (not (eql (car L) (caddr L))))
          (unrepeated-elts (cddr L)))
        (T (unrepeated-elts (cdr L)))))

; (print (unrepeated-elts '(a b a a a c c)))

; Problem 9
; Do exercise 10.4(c) on the same page in Common Lisp. Name your 
; function REPEATED-ELTS.

(defun repeated-elts(L)
  (cond ((endp L)())
        ((or (endp (cdr L)) (not (equal (car L) (cadr L))))
          (repeated-elts (cdr L)))
        ((or (endp (cddr L)) (not (equal (car L)(caddr L))))
          (cons (car L) (repeated-elts (cddr L))))
        (T (repeated-elts(cdr L)))))

; (print (repeated-elts '(a b a a a c c)))

; Problem 10
; Do exercise 10.4(d) on the same page in Common Lisp. Name your 
; function COUNT-REPETITIONS.

(defun count-repetitions (L)
  (cond ((endp L)())
        ((or (endp (cdr L)) (not (eql (car L) (cadr L)))) (cons (list 1 (car L))
          (count-repetitions (cdr L))))
        (T (let ((x (count-repetitions (cdr L)))) (cons (list (+ 1 (caar x))
          (cadar x)) (cdr x))))))

; (print (count-repetitions '(a b a a a c c)))

; Problem 11
; [Exercise 8 on p. 141 of Wilensky] Write a recursive function SUBSET 
; that takes two arguments: a function and a list. SUBSET should apply the 
; function to each element of the list, and return a list of all the elements 
; of the argument list for which the function application returns a true 
; (i.e., non-NIL) value. Example: (subset #'numberp '(a b 2 c d 3 e f)) => (2 3)

(defun subset(f L)
  (cond ((endp L)())
        ((funcall f (car L)) (cons (car L)(subset f (cdr L))))
        (T (subset f (cdr L)))))

; (print (subset #'numberp '(a b 2 c d 3 e f)))

; Problem 12
; Write (i) a recursive function OUR-SOME and (ii) a recursive function 
; OUR-EVERY each of which takes two arguments: a function and a list. 
; OUR-SOME should apply the function to successive elements of the list 
; until the function returns a true (i.e., non-NIL) value, at which point 
; it should return the rest of the list (including the element for which the 
; function just returned a true value).* If the function returns NIL when 
; applied to each of the arguments, OUR-SOME should return NIL. OUR-EVERY 
; should apply the function to successive elements of the list until the 
; function returns NIL, at which point it should return NIL. If the function 
; returns a true value when applied to each of the arguments, then OUR-EVERY 
; should return T. Examples:
;                   (our-some #'numberp '(A B 2 C D))  => (2 C D) 
;                   (our-some #'numberp '(A B C D))    => NIL
;                   (our-every #'symbolp '(A B 2 C D)) => NIL 
;                   (our-every #'symbolp '(A B C D))   => T

(defun our-some(F L)
  (cond ((endp L) nil)
        ((funcall f (car L)) L)
        (T (our-some f (cdr L)))))

(defun our-every(F L)
  (cond ((endp L) T)
        (T (and (funcall f (car L)) (our-every f (cdr L))))))

; (print (our-some #'numberp '(A B 2 C D)))

; Problem 13
; Modify your solutions to problem 7 of Lisp Assignment 4 and problem 4 
; above to produce a solution to exercise 10.6b on p. 419 of Sethi. 
; Name your function QSORT1. (Since PARTITION is used in problem 4, you 
; must use some other name for your modified version of that function.) 
; Examples: (QSORT1 #'> '(2 8 9 5 1 7 3)) => (9 8 7 5 3 2 1)
;           (QSORT1 #'< '(2 8 9 5 1 7 3)) => (1 2 3 5 7 8 9)
;           (QSORT1 (LAMBDA (L1 L2) (< (LENGTH L1) (LENGTH L2)))
;                   '((X) (A D X E G K) (1 2 Q R S) NIL (S D F))) 
;              => (NIL (X) (S D F) (1 2 Q R S) (A D X E G K))

(defun partition1 (L N P)
  (if (endp L)
      '(()())
      (let ((x(partition1 (cdr L) N P)))
           (if (funcall p (car L) N)
               (list (cons (car L) (car x ))(cadr x))
               (list(car x) (cons (car L) (cadr x)))))))

(defun qsort1 (N L)
  (if (endp L)
      nil
      (let ((x (partition1 L (car L) N)))
           (if (endp (car x)) 
               (cons (car L) (qsort1 N (cdr L)))
               (append (qsort1 N (car x))(qsort1 N (cadr X)))))))

; (print (QSORT1 #'> '(2 8 9 5 1 7 3)))

; Problem 14
; Do exercise 10.12a on p. 420 of Sethi in Common Lisp. Example:
; (FOO #'– '(1 2 3 4 5)) 
;   => ((–1 2 3 4 5) (1 –2 3 4 5) (1 2 –3 4 5) (1 2 3 –4 5) (1 2 3 4 –5))

(defun foo (F L)
  (if (endp L)
      nil
      (cons (cons (funcall f (car L))(cdr L))
        (mapcar (lambda (first)(cons(car L) first))
        (foo f (cdr L))))))

; (print (FOO #'- '(1 2 3 4 5)))

; Problem 15
; First, reread the subsection "Recursion Can Be Efficient" on pp. 75 – 8 of 
; Winston and Horn. Then solve the following problems.

; (a) Do exercise 10.5 on p. 419 of Sethi in Common Lisp. Name your functions
;     TR-ADD, TR-MUL and TR-FAC. Examples:
;       (TR-ADD '(1 2 3 4 5) 0) => 15 
;       (TR-MUL '(1 2 3 4 5) 1) => 120 
;       (TR-FAC 5 1) => 120 Note that your definitions of TR-ADD, TR-MUL, and 
;                           TR-FAC must be tail recursive.

(defun tr-add(L N)
  (if (endp L)
        N
      (tr-add (cdr L) (+ (car L) N))))

(defun tr-mul (L N)
  (if (endp L)
        N
      (tr-mul (cdr L) (* (car L) N))))

(defun tr-fac (N res)
  (if (zerop n) 
      res 
      (tr-fac (- n 1) (* n res))))

; (print (TR-ADD '(1 2 3 4 5) 0))
; (print (TR-MUL '(1 2 3 4 5) 1))
; (print (TR-FAC 5 1))

; (b) Wilson's Theorem in number theory states that an integer n > 1 is 
;     prime if and only if (n – 1)! mod n = n – 1. Use this theorem and TR-FAC
;     to write a predicate SLOW-PRIMEP such that if n > 1 is an integer then
;     (SLOW-PRIMEP n) returns T or NIL according to whether or not n is prime.
;     (You may of course use the built-in function MOD.) Test your predicate
;     SLOW-PRIMEP by using it to find the least prime number greater 
;     than 20,000.

(defun slow-primep (n)
  (= (mod (tr-fac (- n  1) 1) n) (- n 1)))

; (compile 'tr-fac)
; (print (slow-primep 22619))

; Problem 16
; A matrix can be represented as a nonempty list of nonempty lists in which 
; the ith element of the jth list is the element in the ith column and jth 
; row of the matrix. For example, ((A B) (C D)) would represent a 2 X 2 matrix
; whose first row contains the elements A and B, and whose second row contains
; the elements C and D. Write three functions TRANSPOSE1, TRANSPOSE2, and 
; TRANSPOSE3, each of which takes a single argument M; if M is a nonempty list 
; of nonempty lists which represents a matrix in the above-mentioned way, then
; each of the three functions should return the list of lists which represents
; the transpose of that matrix. The three functions should work as follows:

; Example (here n may be 1, 2 or 3):
;   (TRANSPOSEn '((1 2 3 4) (5 6 7 8) (9 1 0 1 1 1 2))) 
;        => ((1 5 9) (2 6 1 0) (3 7 1 1) (4 8 1 2))

; (a) (transpose1 M) computes its result from (transpose1 (cdr M)) and 
;     (car M) using mapcar #'cons. [Hint: Take the set of valid values of M 
;     to be the set of lists of one or more nonempty lists that all have the 
;     same length. Then the BC-2 base case is (endp (cdr M)), when the result
;     to be returned is (mapcar #'list (car M)).]

(defun transpose1 (L)                           
  (if (endp (cdr L))
      (mapcar #'list (car L))
      (mapcar #'cons (car L) (transpose1 (cdr L)))))

; (print (transpose1 '((1 2 3 4) (5 6 7 8) (9 1 0 1 1 1 2))))

; (b) (transpose2 M) computes its result from (transpose2 (mapcar #'cdr M)) 
;     and (mapcar #'car M). [Hint: Again, take the set of valid values of M
;     to be the set of lists of one or more nonempty lists that all have the
;     same length. This time, the BC-2 base case is (endp (cdar M)), when the
;     result is (list (mapcar #'car M)).]

(defun transpose2 (L)
  (if (endp (cdar L))
      (list (mapcar #'car L))
      (cons (mapcar #'car L)(transpose2 (mapcar #'cdr L)))))

; (print (transpose2 '((1 2 3 4) (5 6 7 8) (9 1 0 1 1 1 2))))

; (c) (transpose3 M) obtains its result as follows: 
;     (apply #'mapcar (cons #'??? M)) or, equivalently, 
;     (apply #'mapcar #'??? M), where ??? is the name of an appropriate 
;     function.

(defun transpose3 (L)
  (apply #'mapcar #'list L))

; (print (transpose3 '((1 2 3 4) (5 6 7 8) (9 1 0 1 1 1 2))))
