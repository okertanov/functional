(ns Lija.core)

(import
 '(java.awt Color Graphics Dimension GridLayout)
 '(javax.swing JPanel JFrame JLabel JButton))

(defn render [g] (do))

(def width 320)
(def height 240)

(def panel (doto (new JPanel)
            (.setLayout (new GridLayout 0 2 2 2))
            (.add (new JButton ""))
            (.add (new JButton ""))
            (.add (new JButton ""))
            (.add (new JButton ""))))

(defn -main [& args]
  (def frame (doto (new JFrame)
              (.setPreferredSize (new Dimension width height))
              (.setDefaultCloseOperation JFrame/EXIT_ON_CLOSE)
              (.add panel)
              .pack
              .show))
  (println "Welcome to Lija! Args are:" args))
