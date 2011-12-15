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
