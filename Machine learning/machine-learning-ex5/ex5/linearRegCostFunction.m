function [J, grad] = linearRegCostFunction(X, y, theta, lambda)
%LINEARREGCOSTFUNCTION Compute cost and gradient for regularized linear 
%regression with multiple variables
%   [J, grad] = LINEARREGCOSTFUNCTION(X, y, theta, lambda) computes the 
%   cost of using theta as the parameter for linear regression to fit the 
%   data points in X and y. Returns the cost in J and the gradient in grad

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost and gradient of regularized linear 
%               regression for a particular choice of theta.
%
%               You should set J to the cost and grad to the gradient.
%

J = X;
J = J*theta;
J = J - y;
J = J'*J;
J = J/(2*m);

% Regularization

reg_term =  theta'*theta;
reg_term = lambda*reg_term/(2*m);
reg_term = reg_term - lambda*theta(1).^2/(2*m);

J = J + reg_term;

grad = X'*X*theta - X'*y;
grad = grad/m;

theta_0 = theta(1);
grad = grad + lambda*theta/m;
grad(1) = grad(1) - lambda*theta_0/m;






% =========================================================================

grad = grad(:);

end
