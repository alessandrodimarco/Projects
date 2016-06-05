;1. Define a LISP function MIN-2 with the following properties.
;   MIN-2 takes two arguments. If those arguments have values A and B,
;   and A and B are numbers, then MIN-2 returns A if A ≤ B and
;   returns B if A > B; but if A or B is not a number MIN-2 returns the
;   symbol ERROR.
;   Examples: (MIN-2 21.3 7/2) => 7/2    (MIN-2 17.5 29)     => 17.5
;             (MIN-2 5 'APPLE) => ERROR  (MIN-2 '(31) '(54)) => ERROR

(defun min-2 (a b)
    (cond
        ((not (numberp a)) 'ERROR)
        ((not (numberp b)) 'ERROR)
        ((<= a b) a)
        (T b)))

; (print (min-2 "8" 1))

;2. [Exercise 4 on page 72 of Wilensky] Write a LISP function SAFE-AVG that
;   takes 2 arguments and returns the average of those arguments if they are
;   numbers. If one or both of the arguments is not a number, the function
;   should return NIL.
;   Examples: (SAFE-AVG 23 47.4)      => 35.2 (SAFE-AVG 3 8)           => 11/2
;             (SAFE-AVG '(23.1) 47.3) => NIL  (SAFE-AVG 'ORANGE 'PLUM) => NIL

(defun safe-avg (x y)
    (cond
        ((not (numberp x)) nil)
        ((not (numberp y)) nil)
        (T (/ (+ x y) 2))))

;(print (safe-avg 23 47.4))

;3. [Exercise 2 on page 72 of Wilensky] Write a LISP predicate ODD-GT-MILLION
;   that takes one argument, and which returns T if its argument is an odd
;   integer greater than a million, but returns NIL otherwise. Hint: Make use
;   of the predicate INTEGERP.
;   Examples: (ODD-GT-MILLION 2010231)    => T   (ODD-GT-MILLION 171)    => NIL
;             (ODD-GT-MILLION 2010232)    => NIL (ODD-GT-MILLION 21/5)   => NIL
;             (ODD-GT-MILLION 1718671.24) => NIL (ODD-GT-MILLION 'APPLE) => NIL
;             (ODD-GT-MILLION '(2010231)) => NIL

(defun odd-gt-million (x)
    (if (not (integerp x))
        nil
        (if (and (oddp x) (> x 1000000))
            T
            nil)))

;(print (odd-gt-million 21/5))

;4. [Exercise 3 on page 72 of Wilensky] Re-read the discussion of the predicate
;   MEMBER on p. 51 of Winston and Horn. Then write a LISP predicate
;   MULTIPLE-MEMBER that takes two arguments and behaves as follows: If the
;   first argument is a symbol or number and the second is a list, then
;   MULTIPLE-MEMBER returns a true value if the first argument occurs at least
;   twice in the second argument, and returns NIL otherwise.
;   Examples: (MULTIPLE-MEMBER 'A '(B A B B A C A D)) => (A C A D)
;             (MULTIPLE-MEMBER 'A '(B A B B C C A D)) => (A D)
;             (MULTIPLE-MEMBER 'A '(B A B B C D))     => NIL
;   [Notice that the behavior of MULTIPLE-MEMBER is unspecified in cases where
;   the first argument is not a symbol or number, and in cases where the second
;   argument is not a list. In other words, your definition may return any
;   value or produce an evaluation error in such cases.]

(defun multiple-member (x y)
    (if (and (or (numberp x) (symbolp x)) (listp y))
        (member x (cdr (member x y)))
        nil))

; (print (multiple-member 'A '(B A B B A C A D)))

;5. Define a LISP function MONTH->INTEGER which takes as argument a symbol
;   that should be the name of a month, and which returns the number of the
;   month. For example,
;   (MONTH->INTEGER 'MARCH) => 3 and (MONTH->INTEGER 'JUNE) => 6.
;   If the argument is not a symbol that is the name of a month, the
;   function should return the symbol ERROR.
;   Examples: (MONTH->INTEGER 'C)       => ERROR  (MONTH->INTEGER 7) => ERROR
;             (MONTH->INTEGER '(MARCH)) => ERROR

(defun month->integer (month)
    (cond
        ((eql month 'january) 1)
        ((eql month 'february) 2)
        ((eql month 'march) 3)
        ((eql month 'april) 4)
        ((eql month 'may) 5)
        ((eql month 'june) 6)
        ((eql month 'july) 7)
        ((eql month 'august) 8)
        ((eql month 'september) 9)
        ((eql month 'october) 10)
        ((eql month 'november) 11)
        ((eql month 'december) 12)
        (T 'Error)))

; (print (month-integer 'c))

;6. Define a LISP function SCORE->GRADE which takes a single argument, s,
;   and returns a symbol according to the following scheme:
;           s ≥ 90          A       73 ≤ s < 77     C+
;           87 ≤ s < 90     A-      70 ≤ s < 73     C
;           83 ≤ s < 87     B+      60 ≤ s < 70     D
;           80 ≤ s < 83     B       s < 60          F
;           77 ≤ s < 80     B-
;
;   If the argument s is not a number then the function should return NIL.
;   Examples:   (SCORE->GRADE 86.3)    => B+    (SCORE->GRADE 106)  => A
;               (SCORE->GRADE -10.1)   => F     (SCORE->GRADE 59.9) => F
;               (SCORE->GRADE 83)      => B+    (SCORE->GRADE 74)   => C+
;               (SCORE->GRADE 67)      => D     (SCORE->GRADE 87.0) => A–
;               (SCORE->GRADE '(86.3)) => NIL   (SCORE->GRADE 'DOG) => NIL

(defun score->grade (s)
    (cond
        ((not (numberp s)) nil)
        ((>= s 90) 'A)
        ((>= s 87) 'A-)
        ((>= s 83) 'B+)
        ((>= s 80) 'B )
        ((>= s 77) 'B-)
        ((>= s 73) 'C+)
        ((>= s 70) 'C)
        ((>= s 60) 'D)
        ((< s 60) 'F)))

; (print (SCORE->GRADE '(86.3)))

;7. Define a LISP function GT with the following properties. GT takes two
;   arguments. It returns T if both arguments are numbers and the first argument
;   is strictly greater than the second. In all other cases GT returns NIL.

(defun GT (x y)
    (and (numberp x) (numberp y) (> x y)))

;(print (GT 10 9))

;8. Define a LISP function SAME-SIGN with the following properties.
;   SAME-SIGN takes two arguments. It returns T if both arguments are equal to
;   zero, if both are negative numbers, or if both are positive numbers. In all
;   other cases SAME-SIGN returns NIL.
;   Examples:   (SAME-SIGN 0 –2)  => NIL     (SAME-SIGN –3 –9) => T
;               (SAME-SIGN 'A 'A) => NIL

(defun same-sign (x y)
    (and
        (numberp x)
        (numberp y)
        (or (and (eql x 0) (eql y 0))
            (and (< x 0) (< y 0))
            (and (> x 0) (> y 0)))))

; (print (same-sign 5 10))

;9. Define a LISP function SAFE-DIV with the following properties. SAFE-DIV
;   takes two arguments. If both arguments are numbers and the second is not
;   equal to zero, then it returns the result of dividing the first argument
;   by the second. In all other cases it returns NIL.
;   Examples: (SAFE-DIV 6 4)    => 3/2     (SAFE-DIV 6.0 4) => 1.5
;             (SAFE-DIV 6 0)    => NIL     (SAFE-DIV 6 0.0) => NIL
;             (SAFE-DIV '(6) 4) => NIL

(defun safe-div (x y)
    (and
        (numberp x)
        (numberp y)
        (not (= y 0))
        (/ x y)))

; (print (safe-div '(6) 4))
