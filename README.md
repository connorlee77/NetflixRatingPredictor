# UMRatingPredictor
Movie rating predictor

These are machine learning models implemented for the netflix prize challenge. The main models include SVD and SVD++. The SVD takes into account global rating averages, user and movie rating biases, along with the user and movie feature vectors. The SVD++ model extends the SVD to include implicit user feedback. Baseline predictions such as temporal effects were also implemented but not submitted as a final solution. In the matrix factorization models, stochastic gradient descent was used to train the feature vectors. Hogwild! was used as a lock-free parallelization technique to speed up an iteration of SGD. Adaptive learning rates and the technique, "search, then converge," was also used to speed up the convergence of SGD. 
