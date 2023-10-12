document.addEventListener('DOMContentLoaded', () => {
  let count = 0
  const countDisplay = document.getElementById('counterValue')
  const btnPlus = document.getElementById('plus')
  const btnMinus = document.getElementById('minus')

  const updateDisplay = () => {
    countDisplay.textContent = count
  }

  btnPlus.addEventListener('click', function () {
    count++
    updateDisplay()
  })

  btnMinus.addEventListener('click', function () {
    count--
    updateDisplay()
  })

  updateDisplay()
})
