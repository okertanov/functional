(ns Lija.core)

(import
  '(java.awt Color Graphics Dimension GridLayout)
  '(javax.swing JPanel JFrame JLabel JButton))

(defprotocol Dimension-protocol
  (create-dimension [this]
    "Creates new Dimension class"))

(defrecord size [w h]
  Dimension-protocol
    (create-dimension [this] (new Dimension w h)))

(def wsize
  (size. 320 240))

(defn layout []
  (new GridLayout 0 2 2 2))

(def panel
  (doto (new JPanel)
    (.setLayout (layout))
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
