
(cl:in-package :asdf)

(defsystem "map_merge-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ConfigICP" :depends-on ("_package_ConfigICP"))
    (:file "_package_ConfigICP" :depends-on ("_package"))
    (:file "ICPStat" :depends-on ("_package_ICPStat"))
    (:file "_package_ICPStat" :depends-on ("_package"))
  ))