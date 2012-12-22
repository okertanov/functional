(ns clap.core
  (:gen-class))

(use '(incanter core stats charts))

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  (println "Hello, World!")
  (view (histogram (sample-normal 1000))))

