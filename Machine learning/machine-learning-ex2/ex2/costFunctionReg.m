function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta

Z = X*theta;
K = sigmoid(Z);
J = -transpose(y)*log(K) - (transpose(1-y)*log(1-K));
J = J/m;

M = theta(2:end);
M = M.^2;
M = lambda*sum(M)/(2*m);

J = J + M;

grad = transpose(X)*(K-y);
grad = grad/m;

theta_0 = theta(1);
grad = lambda*theta/m + grad;
grad(1) = grad(1) - lambda*theta_0/m;



% =============================================================

end
