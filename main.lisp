(defun get-file (filename)
  (with-open-file (stream filename)
		  (loop for lines = (read-line stream nil)
			while line
			collect line)))
