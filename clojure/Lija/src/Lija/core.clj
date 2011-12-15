;;
;; Copyright (c) 2011 Oleg Kertanov <okertanov@gmail.com>
;;

;; * To use:
;;   lein plugin install swank-clojure 1.3.4-SNAPSHOT
;;   then from inside a project, invoke M-x clojure-jack-in
;; * SLIME Commands
;;   M-.: Jump to the definition of a var
;;   C-c TAB: Autocomplete symbol at point
;;   C-x C-e: Eval the form under the point
;;   C-c C-k: Compile the current buffer
;;   C-c C-l: Load current buffer and force required namespaces to reload
;;   C-M-x: Compile the whole top-level form under the point.
;;   C-c S-i: Inspect a value
;;   C-c C-m: Macroexpand the call under the point
;;   C-c C-d C-d: Look up documentation for a var
;;   C-c C-z: Switch from a Clojure buffer to the repl buffer
;;   C-c M-p: Switch the repl namespace to match the current buffer
;;   C-c C-w c: List all callers of a given function

(ns Lija.core)

(import
  '(java.awt Color Graphics Dimension GridLayout)
  '(javax.swing JPanel JFrame JLabel JButton))

(defprotocol Dimension-protocol
  (create-dimension [th]
    "Creates new Dimension class"))

(defrecord Size [w h]
  Dimension-protocol
    (create-dimension [th] (new Dimension w h)))

(def wsize
  (Size. 320 240))

(defn create-grid-layout []
  (new GridLayout 0 2 2 2))

(def panel
  (doto (new JPanel)
    (.setLayout (create-grid-layout))
    (.add (new JButton ""))
    (.add (new JButton ""))
    (.add (new JButton ""))
    (.add (new JButton ""))))

(defn -main [& args]
  (def frame
    (doto (new JFrame)
    (.setPreferredSize (.create-dimension wsize))
    (.setDefaultCloseOperation JFrame/EXIT_ON_CLOSE)
    (.add panel)
    .pack
    .show))
  (println "Welcome to Lija! Args are:" args))
