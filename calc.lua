function calculo (x, y)
  return (x^2 * math.sin(y))/(1 + x)
end

function bhaskara(a,b,c)
  delta = math.sqrt(b*b - 4*a*c)
  x1 = (-b + delta) / (2*a)
  x2 = (-b - delta) / (2*a)
  -- return x1, x2
  return x1, x2
end


function factorial(n)
  result = 1
  for i=n, 2, -1 do
    result = result * i
  end
  return result
end