; 1. Define a recursive function SUM with the properties stated in problem A.
; Note that whereas NIL is not a valid argument of MY-SUM, NIL is a valid
; argument of SUM.

(defun sum (L)
  (if (endp L)
    0
    (+ (car L) (sum (cdr L)))))

; (print (sum '(1 2 3)))

; 2. Define a recursive function NEG-NUMS with the properties stated in
; problem B. Note that NIL is a valid argument of NEG-NUMS.

(defun neg-nums (L)
  (if (endp L)
    nil
    (if (minusp (car L))
      (cons (car L) (neg-nums (cdr L)))
      (neg-nums (cdr L)))))

; (print (neg-nums '(-2 3 -5 6 3)))

; 3. Define a recursive function INC-LIST-2 with the properties stated in
; problem C. Note that the first argument of INC-LIST-2 may be NIL.

(defun inc-list-2 (L N)
  (if (endp L)
    nil
    (cons (+ (car L) N) (INC-LIST-2 (cdr L) N))))

; (print (INC-LIST-2 '(-2 3 -5 6 3) 6))

; 4. Define a recursive function INSERT with the properties stated in problem D.
; Note that the second argument of INSERT may be NIL.

(defun insert (N L)
  (if (endp L)
    (list N)
    (if (< N (car L))
      (cons N L)
      (cons (car L) (insert N (cdr L))))))

; (print (insert 4 '(0 0 1 3 3 7 8 8)))

; 5. Define a recursive function ISORT with the properties stated in problem E.
; Hint: In your definition of ISORT you should not have to call any function
; other than ISORT itself, INSERT, CAR, CDR, and ENDP. (A special form such
; IF or COND is not considered to be a function, and will be needed.)

(defun isort (L)
  (if (endp L)
    nil
    (insert (car L) (isort (cdr L)))))

; (print (isort '(9 4 1 7 3 6)))

; 6. Define a recursive function SPLIT-LIST with the properties stated in
; problem F.

(defun split-list (L)
  (if (endp L)
    '(nil nil)
    (let ((X (split-list (cdr L))))
      (list (cons (car L) (cadr X)) (car X)))))

; (print (split-list '(B C D 1 2 3 4 5)))

; 7. Define a recursive function PARTITION with the properties stated in
; problem G.

(defun partition (L P)
  (if (endp L)
    '(nil nil)
    (let ((X (partition (cdr L) P)))
      (if (< (car L) P)
        (list (cons (car L) (car X)) (cadr X))
        (list (car X) (cons (car L) (cadr X)))))))

; (print (partition '(4 0 5 3 1 2 4 1 4) 4))


; 8. Without using MEMBER, complete the following definition of a recursive
; function POS such that if L is a list and E is an element of L then (POS E L)
; returns the position of the first occurrence of E in L, and such that if E is
; not an element of L then (POS E L) returns 0.

(defun pos (E L)
  (cond ((endp L) 0)
    ((equal (first L) E) 1)
    (T (let ((X (pos E (rest L))))
         (if (not (zerop X)) (+ 1 X) X)))))

; (print (pos 5 '(1 2 5 3 5 5 1 5)))

; 9. Define a recursive function SPLIT-NUMS such that if N is a non-negative
; integer then (SPLIT-NUMS N) returns a list of two lists: The first of the two
; lists consists of the even integers between 0 and N in descending order,
; and the other list consists of the odd integers between 0 and N in
; descending order.

(defun split-nums (N)
  (if (zerop n)
    '((0) ())
    (let ((x (split-nums (- n 1))))
      (if (evenp N)
        (list (cons N (first x)) (second x))
        (list (first x) (cons N (second x)))))))

; (print (split-nums 7))

; 10. Define a recursive function SET-UNION such that if s1 and s2 are sets
; then (SET-UNION s1 s2) is a set that contains the elements of s1 and the
; elements of s2, but no other elements. Thus (SET-UNION '(A B C D) '(C E F))
; should return a list consisting of the atoms A, B, C, D, E, and F
; (in any order) in which no atom occurs more than once.

(defun set-union (s1 s2)
  (cond ((endp s1) s2)
    ((member (car s1) s2) (set-union (cdr s1)s2))
    (T (cons (car s1) (set-union (cdr s1) s2)))))

; (print (SET-UNION '(A B C D) '(C E F)))

; 11. Define a recursive function SET-REMOVE such that if s is a set and x is
; an atom in s then (SET-REMOVE x s) is a set that consists of all the elements
; of s except x, but if s is a set and x is an atom which is not in s then
; (SET-REMOVE x s) returns a set that is equal to s.

(DEFUN set-remove (X S)
  (if (endp S)
    nil
    (let ((R (set-remove X (cdr S))))
      (if (not (equal (car S) X))
        (cons (car S) R)
        R))))

; (print (set-remove 'B '(A B C D)))

; 12. Define a recursive function SET-EXCL-UNION such that if s1 and s2 are
; sets then (SET-EXCL-UNION s1 s2) is a set that contains all those atoms that
; are elements of exactly one of s1 and s2, but no other atoms.
; (SET-EXCL-UNION s1 s2) does not contain any atoms that are neither in s1 nor
; in s2, and also does not contain the atoms that are in both of s1 and s2. For
; example, (SET-EXCL-UNION '(A B C D) '(E C F G A)) should return a list
; consisting of the atoms B, D, E, F, and G (in any order) in which no atom
; occurs more than once.

(defun set-excl-union(s1 s2)
  (if (endp s1)
    s2
    (if (member (car s1) s2)
      (set-remove (car s1) (set-excl-union (cdr s1) s2))
      (cons (car s1) (set-excl-union (cdr s1) s2)))))

; (print (set-excl-union '(A B C D) '(E C F G A)))

; 13. Define a recursive function SINGLETONS such that if e is a list of
; numbers and/or symbols then (SINGLETONS e) is a set that consists of all the
; atoms that occur just once in e. Examples: (SINGLETONS ( )) => NIL
; (SINGLETONS '(G A B C B)) => (G A C) (SINGLETONS'(HGABCB))=>(HGAC)
; (SINGLETONS'(AGABCB))=>(GC) (SINGLETONS '(B G A B C B)) => (G A C)
; [Hint: When e is nonempty, consider the case in which (car e) is a member of
; (cdr e), and the case in which (car e) is not a member of (cdr e).]

(defun singletons (e)
  (if (endp e)
    nil
    (if (member (first e) (rest e))
      (set-remove (first e) (singletons (rest e)))
      (cons (first e) (singletons (rest e))))))

; (print (singletons '(G A B C B)))
